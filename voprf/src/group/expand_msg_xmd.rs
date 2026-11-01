// Copyright (c) Meta Platforms, Inc. and affiliates.
//
// This source code is dual-licensed under either the MIT license found in the
// LICENSE-MIT file in the root directory of this source tree or the Apache
// License, Version 2.0 found in the LICENSE-APACHE file in the root directory
// of this source tree. You may select, at your option, one of the above-listed
// licenses.

//! RFC 9380 Expand-Message-XMD implementation.

use digest::core_api::BlockSizeUser;
use digest::{Digest, FixedOutput, HashMarker, Update};
use generic_array::typenum::{IsLess, IsLessOrEqual, Unsigned, U256};
use generic_array::GenericArray;

use crate::InternalError;

const OVERSIZE_DST_SALT: &[u8] = b"H2C-OVERSIZE-DST-";
const MAX_DST_LEN: usize = 255;

enum Domain<'a, L: generic_array::ArrayLength<u8>> {
    Hashed(GenericArray<u8, L>),
    Array(&'a [&'a [u8]]),
}

impl<'a, L: generic_array::ArrayLength<u8> + IsLess<U256>> Domain<'a, L> {
    fn xmd<X: Digest<OutputSize = L>>(dsts: &'a [&'a [u8]]) -> Result<Self, InternalError> {
        if dsts.is_empty() {
            Err(InternalError::Input)
        } else if dsts.iter().map(|dst| dst.len()).sum::<usize>() > MAX_DST_LEN {
            let mut hash = X::new();
            hash.update(OVERSIZE_DST_SALT);
            for dst in dsts {
                hash.update(dst);
            }
            Ok(Self::Hashed(hash.finalize()))
        } else {
            Ok(Self::Array(dsts))
        }
    }

    fn update_hash<HashT: Update>(&self, hash: &mut HashT) {
        match self {
            Self::Hashed(d) => hash.update(d),
            Self::Array(d) => {
                for d in d.iter() {
                    hash.update(d);
                }
            }
        }
    }

    fn len(&self) -> u8 {
        match self {
            Self::Hashed(_) => L::to_u8(),
            Self::Array(d) => {
                let total: usize = d.iter().map(|d| d.len()).sum();
                u8::try_from(total).unwrap_or(255)
            }
        }
    }
}

pub fn expand_message_xmd<H>(
    msgs: &[&[u8]],
    dsts: &[&[u8]],
    out: &mut [u8],
) -> Result<(), InternalError>
where
    H: BlockSizeUser + Default + FixedOutput + HashMarker,
    H::OutputSize: IsLess<U256> + IsLessOrEqual<H::BlockSize>,
{
    let len_in_bytes = out.len();
    if len_in_bytes == 0 || len_in_bytes > 65535 {
        return Err(InternalError::Input);
    }
    let len_in_bytes_u16 = u16::try_from(len_in_bytes).map_err(|_| InternalError::Input)?;
    let b_in_bytes = H::OutputSize::to_usize();
    let ell = (len_in_bytes + b_in_bytes - 1) / b_in_bytes;
    if ell > 255 {
        return Err(InternalError::Input);
    }
    let ell = u8::try_from(ell).map_err(|_| InternalError::Input)?;

    let domain = Domain::<H::OutputSize>::xmd::<H>(dsts)?;

    // b_0 = H(Z_pad || msg || l_i_b_str || 0 || DST_prime || len(DST_prime))
    let mut b_0 = H::default();
    b_0.update(&GenericArray::<u8, H::BlockSize>::default());
    for msg in msgs {
        b_0.update(msg);
    }
    b_0.update(&len_in_bytes_u16.to_be_bytes());
    b_0.update(&[0]);
    domain.update_hash(&mut b_0);
    b_0.update(&[domain.len()]);
    let b_0 = b_0.finalize_fixed();

    // b_1 = H(b_0 || 1 || DST_prime || len(DST_prime))
    let mut b_vals = H::default();
    b_vals.update(&b_0[..]);
    b_vals.update(&[1u8]);
    domain.update_hash(&mut b_vals);
    b_vals.update(&[domain.len()]);
    let mut b_vals = b_vals.finalize_fixed();

    let mut written = 0;
    let to_copy = b_vals.len().min(len_in_bytes - written);
    out[written..written + to_copy].copy_from_slice(&b_vals[..to_copy]);
    written += to_copy;

    for i in 2..=ell {
        if written >= len_in_bytes {
            break;
        }
        let mut tmp = GenericArray::<u8, H::OutputSize>::default();
        for (j, (b0, bi)) in b_0.iter().zip(&b_vals[..]).enumerate() {
            tmp[j] = b0 ^ bi;
        }
        let mut next_b = H::default();
        next_b.update(&tmp);
        next_b.update(&[i]);
        domain.update_hash(&mut next_b);
        next_b.update(&[domain.len()]);
        b_vals = next_b.finalize_fixed();

        let to_copy = b_vals.len().min(len_in_bytes - written);
        out[written..written + to_copy].copy_from_slice(&b_vals[..to_copy]);
        written += to_copy;
    }

    Ok(())
}

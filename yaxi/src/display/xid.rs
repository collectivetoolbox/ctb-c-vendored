use super::*;

use std::sync::Mutex;

static XID: Mutex<Xid> = Mutex::new(Xid::new());

macro_rules! lock {
    ($mutex:expr) => {
        $mutex.lock().map_err(|_| Error::FailedToLock)
    };
}

pub struct Xid {
    base: u32,
    mask: u32,
    next: u32,
    increment: u32,
}

impl Xid {
    const fn new() -> Xid {
        Xid {
            base: 0,
            mask: 0,
            next: 0,
            increment: 0,
        }
    }

    fn next(&mut self) -> Result<u32, Error> {
        if self.mask == 0 || self.increment == 0 {
            return Err(Error::RanOutOfXid);
        }

        let id = self.base | self.next;
        let Some(candidate) = self.next.checked_add(self.increment) else {
            self.mask = 0;
            self.increment = 0;
            return Ok(id);
        };

        if candidate & !self.mask != 0 {
            self.mask = 0;
            self.increment = 0;
        } else {
            self.next = candidate;
        }

        Ok(id)
    }
}

fn set_allocator_state(lock: &mut Xid, base: u32, mask: u32, next: u32) -> Result<(), Error> {
    let increment = mask & mask.wrapping_neg();
    if mask == 0 || increment == 0 {
        return Err(Error::RanOutOfXid);
    }

    if next & !mask != 0 {
        return Err(Error::InvalidId);
    }

    lock.base = base;
    lock.mask = mask;
    lock.next = next;
    lock.increment = increment;

    Ok(())
}

pub fn setup(base: u32, mask: u32) -> Result<(), Error> {
    let mut lock = lock!(XID)?;

    set_allocator_state(&mut lock, base, mask, 0)
}

pub fn setup_with_next(base: u32, mask: u32, next: u32) -> Result<(), Error> {
    let mut lock = lock!(XID)?;

    set_allocator_state(&mut lock, base, mask, next)
}

pub fn next() -> Result<u32, Error> {
    lock!(XID)?.next()
}

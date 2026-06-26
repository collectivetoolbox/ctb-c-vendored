use std::process::ExitCode;

use clap::Parser;

use self::arg::Args;
use self::arg::Command;

mod arg;
mod common;
mod dump_help;
mod export;
mod extract;
mod filter;
mod format;
mod get;
mod import;
mod io;
mod list;
mod logging;
mod model;
mod progress;
mod self_;
mod verify;

pub fn run() -> ExitCode {
    let exit_code = run_from(std::env::args_os());
    ExitCode::from(exit_code as u8)
}

pub fn run_from<I, T>(args: I) -> i32
where
    I: IntoIterator<Item = T>,
    T: Into<std::ffi::OsString> + Clone,
{
    match run_impl_from(args) {
        Ok(exit_code) => exit_code,
        Err(error) => {
            if let Some(clap_err) = error.downcast_ref::<clap::Error>() {
                let _ = clap_err.print();
                return clap_err.exit_code();
            }
            tracing::error!(?error);
            eprintln!("{:#}", error);
            1
        }
    }
}

fn run_impl_from<I, T>(args: I) -> anyhow::Result<i32>
where
    I: IntoIterator<Item = T>,
    T: Into<std::ffi::OsString> + Clone,
{
    if self::self_::is_installer() {
        self::self_::install_interactive()?;
        return Ok(0);
    }

    let args = Args::try_parse_from(args)?;

    if args.quiet {
        self::progress::disable_global_progress_bar();
    }

    self::logging::set_up_logging(args.log_level, args.log_file.as_deref(), args.log_json)?;

    let exit_code = match args.command {
        Command::Export(args) => {
            self::export::export(&args)?;
            0
        }
        Command::Import(args) => {
            self::import::import(&args)?;
            0
        }
        Command::List(args) => {
            self::list::list(&args)?;
            0
        }
        Command::Get(args) => {
            self::get::get(&args)?;
            0
        }
        Command::Extract(args) => {
            self::extract::extract(&args)?;
            0
        }
        Command::Verify(args) => self::verify::verify(&args)? as i32,
        Command::Self_(args) => {
            self::self_::self_(&args)?;
            0
        }
        Command::DumpHelp => {
            self::dump_help::dump_help()?;
            0
        }
    };

    self::progress::global_progress_bar().println("Done.")?;

    Ok(exit_code)
}

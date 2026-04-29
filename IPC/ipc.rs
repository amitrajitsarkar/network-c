use std::io::Write;
use std::process::{Command, Stdio};

fn main() {
    let mut child = Command::new("cat") // child process
        .stdin(Stdio::piped())
        .stdout(Stdio::piped())
        .spawn()
        .expect("failed to spawn");

    // write to child's stdin (pipe)
    let mut stdin = child.stdin.take().unwrap();
    stdin.write_all(b"Hello from parent\n").unwrap();

    // read from child's stdout (pipe)
    let output = child.wait_with_output().unwrap();

    println!("Child received: {}", String::from_utf8_lossy(&output.stdout));
}

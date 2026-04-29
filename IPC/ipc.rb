r, w = IO.pipe   # create pipe

pid = fork

if pid.nil?
  # Child process
  w.close              # close write end
  msg = r.gets         # read from pipe
  puts "Child received: #{msg}"
  r.close
else
  # Parent process
  r.close              # close read end
  w.puts "Hello from parent"
  w.close
  Process.wait(pid)
end

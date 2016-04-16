require 'test/unit/assertions'

def invoke(command)
  `ssh -oStrictHostKeyChecking=no root@rpi2 #{command}`
end

Given (/^there is no picture yet$/) do
  invoke('rm -f picture.jpg')
end

When (/^the doorbell rings$/) do
  enabled = invoke('"ls /sys/class/gpio | grep 24"').strip
  if enabled != 'gpio24'
    invoke('"echo 24 > /sys/class/gpio/export"')
  end
  invoke('"echo out > /sys/class/gpio/gpio24/direction"')
  invoke('"echo 1 > /sys/class/gpio/gpio24/value"')
  sleep 0.02
  invoke('"echo 0 > /sys/class/gpio/gpio24/value"')
end

Then (/^the internet module takes a picture$/) do
  result = invoke('ls picture.jpg')
  assert_equal 'picture.jpg', result.strip
end


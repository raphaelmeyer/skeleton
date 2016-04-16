#require 'rspec/expectations'
#
#Given (/^there is no picture yet$/) do
#  `ssh root@rpi2 rm -f picture.jpg`
#end
#
#When (/^the doorbell rings$/) do
#  `ssh root@rpi2 echo "5" > "/sys/class/gpio/export`
#  `ssh root@rpi2 echo "out" > "/sys/class/gpio/gpio5/direction`
#  `ssh root@rpi2 echo "1" > "/sys/class/gpio/gpio5/value`
#  # wait 20ms
#  `ssh root@rpi2 echo "0" > "/sys/class/gpio/gpio5/value`
#end
#
#Then (/^the internet module takes a picture$/) do
#  @result = `ssh root@rpi2 ls picure.jpg`
#end


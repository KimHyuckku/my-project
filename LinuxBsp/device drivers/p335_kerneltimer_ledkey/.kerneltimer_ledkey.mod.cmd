cmd_/home/ubuntu/pi_bsp/drivers/p335_kerneltimer_ledkey/kerneltimer_ledkey.mod := printf '%s\n'   kerneltimer_ledkey.o | awk '!x[$$0]++ { print("/home/ubuntu/pi_bsp/drivers/p335_kerneltimer_ledkey/"$$0) }' > /home/ubuntu/pi_bsp/drivers/p335_kerneltimer_ledkey/kerneltimer_ledkey.mod

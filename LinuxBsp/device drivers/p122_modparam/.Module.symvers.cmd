cmd_/home/ubuntu/pi_bsp/drivers/p122_modparam/Module.symvers :=  sed 's/ko$$/o/'  /home/ubuntu/pi_bsp/drivers/p122_modparam/modules.order | scripts/mod/modpost -m -a    -o /home/ubuntu/pi_bsp/drivers/p122_modparam/Module.symvers -e -i Module.symvers -T - 

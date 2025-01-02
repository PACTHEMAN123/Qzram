cmd_/home/xjy/byteless/Module.symvers := sed 's/\.ko$$/\.o/' /home/xjy/byteless/modules.order | scripts/mod/modpost -m -a  -o /home/xjy/byteless/Module.symvers -e -i Module.symvers   -T -

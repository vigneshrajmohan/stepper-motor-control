# stepper-motor-control
Arduino code to control a stepper motor like you would a servo


The stepper I used: https://www.amazon.com/STEPPERONLINE-Stepper-178-5oz-1-26Nm-Stepping/dp/B00PNEPF5I/ref=pd_vtp_h_pd_vtp_h_sccl_6/140-2453761-2276650?pd_rd_w=ixoRn&content-id=amzn1.sym.a5610dee-0db9-4ad9-a7a9-14285a430f83&pf_rd_p=a5610dee-0db9-4ad9-a7a9-14285a430f83&pf_rd_r=7HB2PKQYRKJ3EVFZC30F&pd_rd_wg=aeBNn&pd_rd_r=f1a5dc1f-bedd-4239-9dca-8cdc07f0ba04&pd_rd_i=B00PNEPF5I&psc=1

The driver I used: https://www.amazon.com/Digital-Microstep-Stepper-Controller-2-phase/dp/B07YWZRXGR/ref=sr_1_17_sspa?crid=2C65SIYOJKOGM&keywords=nema23+stepper&qid=1681145748&sprefix=nema23+stepper%2Caps%2C67&sr=8-17-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEyRUpEMTFRTkNISDNHJmVuY3J5cHRlZElkPUEwNjIzNTM3MjFISlo1MDBTOE5MTyZlbmNyeXB0ZWRBZElkPUEwNjY5OTAzM0JTODFOMlhQVVpYVyZ3aWRnZXROYW1lPXNwX210ZiZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=


stepper_control allows you to send messages in this format in the serial baud 9600: "m[current_motor_position],[desired_motor_position]"
An example could look like: "m0,180" which will take the motor from position 0 to 180. 

There is a python file included to send these commands over serial from the python script. It uses a function wrapper that allows you to just call "move_to(180)" and it will read the current_motor_position from the motor1_angle.txt file. 

email me if you have questions
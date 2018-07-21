void getDanger(){
  if( dangerOverride == true){
    dangerM1 = false;
    dangerM2 = false;
    dangerM3 = false;
    dangerM4 = false;
    dangerM5 = false;
    dangerM6 = false;   

    dangerFront = false;
    dangerBack = false;

  }

  else {

    if(mode == MODE_ROVER){

          buttonStateFront_R = digitalRead(BUTTON_PIN_FRONT_R);
          buttonStateBack_R = digitalRead(BUTTON_PIN_BACK_R);
          buttonStateFront_L = digitalRead(BUTTON_PIN_FRONT_L);
          buttonStateBack_L = digitalRead(BUTTON_PIN_BACK_L);         

          if (buttonStateFront_R == LOW || buttonStateFront_L == LOW){
            dangerFront = true;
          }
          else {
            dangerFront = false;
          }
    
          if (buttonStateBack_R == LOW  || buttonStateBack_L == LOW){
            dangerBack = true;
          }

          else{
            dangerBack = false;
          }
    }
    else if( mode == MODE_ARM){
      if(dangerCounter == 50){
        
//        roboclaw1.ReadCurrents(address, currentM1, currentM2);
//        roboclaw2.ReadCurrents(address, currentM3, currentM4);
//        roboclaw3.ReadCurrents(address, currentM5, currentM6);
        
        if(currentM1 > M1_thresh){
          dangerM1 = true;
        }

        else if(currentM2 > M2_thresh){
          dangerM2 = true;
        }

        else if(currentM3 > M3_thresh){
          dangerM3 = true;
        }

        else if(currentM4 > M4_thresh){
          dangerM4 = true;
        }

        else if(currentM5 > M5_thresh){
          dangerM5 = true;
        }

        else if(currentM6 > M6_thresh){
          dangerM6 = true;
        }

        dangerCounter=0;

      }
   
      dangerCounter++;        
          
        
    }
  }
}

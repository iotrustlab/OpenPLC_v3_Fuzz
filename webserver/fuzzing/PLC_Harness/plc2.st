PROGRAM plc2
  VAR
    ColorSensor_RED AT %QW0 : INT;
    ColorSensor_GREEN AT %QW1 : INT;
    ColorSensor_BLUE AT %QW2 : INT;
    RangeSensor AT %QW3 : INT;
    Pump AT %QX0.4 : BOOL := FALSE;
    Doser_RED AT %QX0.6 : BOOL := FALSE;
    Doser_BLUE AT %QX0.7 : BOOL := FALSE;
  END_VAR
  VAR
    settleTime : TIME := T#700ms;
    doseTime : TIME := T#2000ms;
  END_VAR
  VAR
    treatmentComplete AT %QX0.0 : BOOL := FALSE;
    stage AT %QW4 : INT := 0;
  END_VAR
  VAR
    desiredDistanceFill : REAL := 7.0;
  END_VAR
  VAR
    measuredDistance AT %QD1 : REAL;
  END_VAR
  VAR
    minRed : INT := 20;
    doserRedTimer : TON;
    doserBlueTimer : TON;
    settleTimer : TON;
  END_VAR
  VAR
    doseTimerDone AT %QX1.2 : BOOL := 0;
  END_VAR
  VAR
    settleEN : BOOL := FALSE;
  END_VAR


  (*Workaround to distance measure bug*)
  measuredDistance :=  INT_TO_REAL(RangeSensor)/100.0;
  desiredDistanceFill := 7.0;
  minRed := 20;
  doseTime := T#3000ms;
  settleTime := T#5000ms;

  doserRedTimer(IN:=Doser_RED, PT:=doseTime);
  doserBlueTimer(IN:=Doser_BLUE,PT:=doseTime);
  doseTimerDone := doserRedTimer.Q;
  settleTimer(IN:=settleEN, PT:=settleTime);

  CASE stage OF
      0:  (*Filling stage: it will fill up to a certain amount that corresponds to a certain distance*)
      
          IF measuredDistance > desiredDistanceFill THEN
            Pump := TRUE;
          ELSE
            Pump := FALSE;
            stage := 1;
          END_IF;
          
     1:  (*Treatment stage*)
      
          IF ColorSensor_RED < minRed THEN (*Ensure minimum red value is inserted*)
            stage := 2;
            Doser_RED := TRUE;
            
          ELSIF ColorSensor_RED > ColorSensor_BLUE  THEN (*Ensure blue quantity is > Red *)
            
              stage := 3;
              Doser_BLUE := TRUE;
          
          ELSE  (*Treatment complete*)
            
            stage := 5;
            
          END_IF;
          
      2:  (*Red Dosing Stage*)
      
          IF doserRedTimer.Q THEN
            Doser_RED := FALSE;
            stage := 4;
            settleEN := True;
            (*settleTimer(IN:= True, PT:= settleTime); (*let the dose settle*)
          END_IF;
          
      3: (* Blue Dosing Stage*)
      
          IF doserBlueTimer.Q THEN
            Doser_BLUE := FALSE;
            stage := 4;
            settleEN := True;
          END_IF;
          
      4: (*Settling Stage for Dosage*)
      
          IF settleTimer.Q THEN
            stage := 1;
            settleEN := False;
          END_IF;
      
      5: (*Treatment Complete*)
      
        treatmentComplete := TRUE;
        
  END_CASE;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : plc2;
  END_RESOURCE
END_CONFIGURATION

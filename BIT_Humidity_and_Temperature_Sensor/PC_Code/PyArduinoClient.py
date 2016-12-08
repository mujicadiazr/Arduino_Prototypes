import serial
import time
ser = serial.Serial('COM10', 9600, timeout=1)
file = open("data.txt", "w")
 
while 1:
    try:
        data = ser.readline()
            
        year = time.gmtime()[0]
        month = time.gmtime()[1]
        day = time.gmtime()[2]
        hour = time.gmtime()[3]
        minute = time.gmtime()[4]
        second = time.gmtime()[5]
                
        data = str(year)+ '/' + str(month)+ '/' + str(day)+ ' ' + str(hour)+ ':' + str(minute)+ ':' + str(second)+' ' +data
        
        print data 
        file.writelines(data)       
         
        time.sleep(1)
    except ser.SerialTimeoutException:
        print('Data could not be read')
        time.sleep(1)
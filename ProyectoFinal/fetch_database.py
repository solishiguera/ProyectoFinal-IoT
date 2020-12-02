# Diego was here :)  
from firebase import firebase
import time


def fetch_data_and_store(firebase): 
    """This function will fetch data and store it"""
    cycles = 0

    while cycles < 200:
        # Gets data from DB attribute
        """
        Luz_Diego = firebase.get('Luz_Diego','')
        Agua = firebase.get('Agua','')
        Distancia = firebase.get('Distance','')
        HumedadFer = firebase.get('HumedadFer','')
        LEDEber = firebase.get('LEDEber','')
        LEDRGB = firebase.get('LEDRGB','')
        TempBruno = firebase.get('TempBruno','')
        TempFer = firebase.get('TemperaturaFer','')

        LEDEber = firebase.get('LEDEber','')
        alarm = firebase.get('Alarm','')
        """

        TempFer = firebase.get('TemperaturaFer','')
        LEDRGB = firebase.get('LEDRGBFer','')

        with open("TempFer.txt", "a") as file8:
            file8.write("\n")
            file8.write(str(TempFer))

        with open("LEDRGB.txt", "a") as file6:
            file6.write("\n")
            file6.write(str(LEDRGB))



        """
        with open("LEDEber.txt", "a") as file5:
            file5.write("\n")
            file5.write(str(LEDEber))
        
        with open("Alarm.txt", "a") as file3:
            file3.write("\n")
            file3.write(str(alarm))

        with open("Luz_Diego.txt", "a") as file1:
            file1.write("\n")
            file1.write(str(Luz_Diego))

        with open("Agua.txt", "a") as file2:
            file2.write("\n")
            file2.write(str(Agua))


        with open("HumedadFer.txt", "a") as file4:
            file4.write("\n")
            file4.write(str(HumedadFer))
        

        with open("LEDRGB.txt", "a") as file6:
            file6.write("\n")
            file6.write(str(LEDRGB))

        with open("TempBruno.txt", "a") as file7:
            file7.write("\n")
            file7.write(str(TempBruno))

        with open("TempFer.txt", "a") as file8:
            file8.write("\n")
            file8.write(str(TempFer))
        """
        cycles += 1
    file1.close()
    """
    file2.close()
    file3.close()
    file4.close()
    file5.close()
    file6.close()
    file7.close()
    file8.close()
    """


def main():
    my_firebase = firebase.FirebaseApplication("https://equipocinco-iot.firebaseio.com/")
    fetch_data_and_store(my_firebase)

main() 
#This code was written while I was a either a sophmore or junior in highschool

import tkinter
from tkinter import *


# create the window
win = tkinter.Tk()

#modify the window
win.title("REFtech Score Board")
win.geometry("1000x800")


#frames

frame = Frame(win, bg="Black")
frame.pack()


frame.place(height=1000, width=1000, x=0, y=0)

#variables

greenScore = 0
redScore = 0

time = 10000
#############CONTROLS**********************************************CONTROLS

#base score displays
    #create the displays
greenScoreDisp = Label (frame, text = greenScore, bg= "black", fg = "white", font=("LCD", 80))#create the greenScore Display
greenScoreDisp.place(x=150, y=30)

redScoreDisp = Label (frame, text = redScore, bg= "black", fg = "white", font=("LCD", 80))#create the red score display
redScoreDisp.place(x=750, y=30)
def greenDisp():
    global greenScore
    GSTens = greenScore // 10
    GSOnes = greenScore%10
    GSOut = GSTens, GSOnes
    greenScoreDisp.config(text = GSOut)
greenDisp()

def redDisp():
    global redScore
    RSTens = redScore // 10
    RSOnes = redScore%10
    RSOut = RSTens, RSOnes
    redScoreDisp.config(text = RSOut)
redDisp()


#new key pad input
    #key pad numbers/ middle func between external/digital btns and the input func
def keyPad1():
    keyInput(1)

def keyPad2():
    keyInput(2)
    
def keyPad3():
    keyInput(3)
    
def keyPad4():
    keyInput(4)

def keyPad5():
    keyInput(5)
    
def keyPad6():
    keyInput(6)

def keyPad7():
    keyInput(7)

def keyPad8():
    keyInput(8)

def keyPad9():
    keyInput(9)
    
def keyPad0():
    keyInput(0)
#External Btn functions and bindings
def ExtKey1(event):
    keyPad1()

def ExtKey2(event):
    keyPad2()

def ExtKey3(event):
    keyPad3()

def ExtKey4(event):
    keyPad4()

def ExtKey5(event):
    keyPad5()

def ExtKey6(event):
    keyPad6()

def ExtKey7(event):
    keyPad7()

def ExtKey8(event):
    keyPad8()

def ExtKey9(event):
    keyPad9()

def ExtKey0(event):
    keyPad0()

win.bind("<Key-1>", ExtKey1)
win.bind("<Key-2>", ExtKey2)
win.bind("<Key-3>", ExtKey3)
win.bind("<Key-4>", ExtKey4)
win.bind("<Key-5>", ExtKey5)
win.bind("<Key-6>", ExtKey6)
win.bind("<Key-7>", ExtKey7)
win.bind("<Key-8>", ExtKey8)
win.bind("<Key-9>", ExtKey9)
win.bind("<Key-0>", ExtKey0)

#input function for key pad
ran = 0
numOne = "none"
numTwo = "none"
numThree = "none"
numFour = "none"
clear = False
keyOut = 0,0,0,0

def clearKey():
    global ran
    ran = 5
    keyInput("no")
def keyInput(numPressed): #num imput func
    global numOne
    global numTwo
    global numThree
    global numFour
    global ran
    global clear
    global keyOut
    if (ran < 5):
        ran = ran +1
        clear = False
        keyOut = 0,0,0,0
    else:
        clear = True
    if (clear == True):
        numOne = "none"
        numTwo = "none"
        numThree = "none"
        numFour = "none"
        ran = 1
    if (numPressed == "no"):
        ran = 0
    if (ran == 1):
        numOne = numPressed
    else:
        if (ran == 2):
            numTwo = numPressed
        else:
            if (ran == 3):
                numThree = numPressed
            else:
                if (ran == 4):
                    numFour = numPressed
    if (ran == 1):keyOut =  0, 0, 0, numOne
    else:
        if (ran == 2):keyOut =  0, 0, numOne, numTwo
        else:
            if (ran == 3):keyOut = 0, numOne, numTwo, numThree
            else:
                if (ran == 4):keyOut = numOne, numTwo, numThree, numFour
    if (ran == 0):
        keyOut = 0, 0, 0, 0
    keyDisp(keyOut)
    print(keyOut)
    return keyOut

def keyDisp(keyOut):
    keyInputDisp = Label(frame, text = keyOut, bg= "black", fg = "white", font=("LCD", 20)) #create the key pad output display
    keyInputDisp.place(x = 50, y = 400, width = 100, height = 40)
keyDisp(keyOut)
#functions

#new timer
    #out put Display
timerDisp = Label(win, bg = "black", fg = "white", font=("LCD", 30))#create timer display
timerDisp.place(x=395, y=20, width = 160, height = 50)
    #beginning
StartClicks = 1
Start = False

TimeIn = 0

TimeOut = 0
def Timer():
    global TimeIn
    global Start
    if(Start == True):
         win.after(10, Timer)
    if(TimeIn > 0):
        TimeIn = TimeIn - 1
    else:
        Start = False
    TimeDispConfig(TimeIn)
    return Start
        
def StartPressed():
    global StartClicks
    global Start
    StartClicks =  StartClicks + 1
    if(StartClicks%2 == 0):
        Start = True
        StartBtn.config(text = "Stop", bg = "red")
    else:
        Start = False
        StartBtn.config(text = "Start", bg = "green")
    Timer()
    print (Start)
    return Start

def TimeConfig(Min, Sec):
    global TimeIn
    TimeIn = Min * 6000 + Sec * 100 + 1
    Timer()
    return TimeIn

        
def TimeDispConfig(TimeIn):
    global TimeOut
    Min = TimeIn//6000
    Sec = TimeIn//100 - Min*60
    MinTens = Min//10
    MinOnes = Min%10
    SecTens = Sec//10
    SecOnes = Sec%10
    TimeOut = MinTens, MinOnes, ":", SecTens, SecOnes
    timerDisp.config(text = TimeOut)
    return TimeOut

TimeConfig(2, 0)#starting time

ChangeTimeInt = 1
ChangeTime = False

def ChangeTimeFunc():
    global ChangeTimeInt
    global ChangeTime
    ChangeTimeInt = ChangeTimeInt + 1
    print(ChangeTimeInt)
    if (ChangeTimeInt%2 == 0):
        ChangeTime = True
        if (ChangeBout == True):#making sure that change bout is deactivated
            BoutChange()
        if (ChangeWeight == True):#making sure that change weight is deactivated
            WeightChange()
    else:
        ChangeTime = False
    print(ChangeTime)
    changeTimeLight()
    return ChangeTime

def KeyOutToTimeIn(KeyOut):
    MinTens = KeyOut[0]
    MinOnes = KeyOut[1]
    SecTens = KeyOut[2]
    SecOnes = KeyOut[3]
    Min = MinTens*10 + MinOnes
    Sec = SecTens*10 + SecOnes
    TimeConfig(Min, Sec)
    print(Min, Sec)


        
changeTimeLed = Label(frame, bg = "black")
changeTimeLed.place(x=410, y=165, width = 10, height = 10)

def changeTimeLight():
    global ChangeTime
    if (ChangeTime == True):
        changeTimeLed.config(bg = "green")
    else:
        changeTimeLed.config(bg = "black")
#change the Bout and weight Nums (with notes)
        
BoutChangeInt = 1 #var for num of times btn has been activated
ChangeBout = False #var for whether or not the bout num can be changed
WeightChangeInt = 1
ChangeWeight = False


#create Bout num and Wight class Displays
WeightDisp = Label(frame, bg = "black", fg = "white", text = "0 0 0 0", font=("LCD", 40))#create the Weight class display
WeightDisp.place(width = 144, height =40, x=438, y = 370)

BoutDisp = Label(frame, bg = "black", fg = "white", text = "0 0 0 0", font=("LCD", 40))#create the Weight class display
BoutDisp.place(width = 144, height = 40, x=438, y = 230)


def BoutChange():
    global BoutChangeInt
    global ChangeBout
    global ChangeTime
    global ChangeWeight
    BoutChangeInt = BoutChangeInt + 1
    if (BoutChangeInt%2 == 0):#determining if the bout num can be changed
        ChangeBout = True
        if (ChangeTime == True):#making sure that change time is deativevated
            ChangeTimeFunc()
        if (ChangeWeight == True):#making sure that change weight is deactivated
            WeightChange()
    else:
        ChangeBout = False
    changeBoutLight()

changeBoutLed = Label(frame, bg = "black")#create the  change bout led
changeBoutLed.place(x=410, y=315, width = 10, height = 10)#place the led

def changeBoutLight(): # func to determin whether the Change Bout led will light up or not
    global ChangeBout
    if (ChangeBout == True):
        changeBoutLed.config(bg = "green")
    else:
        changeBoutLed.config(bg = "black")
        
        
def WeightChange():
    global WeightChangeInt
    global ChangeBout
    global ChangeTime
    global ChangeWeight
    WeightChangeInt = WeightChangeInt + 1
    if (WeightChangeInt%2 ==0):#determining if the weight num can be changed
        ChangeWeight = True
        if (ChangeTime == True):#making sure that change time is deativevated
            ChangeTimeFunc()
        if (ChangeBout == True):#making sure that change bout is deactivated
            BoutChange()
    else:
        ChangeWeight = False
    changeWeightLight()
        
changeWeightLed = Label(frame, bg = "black")
changeWeightLed.place(x=410, y=465, width = 10, height = 10)

def changeWeightLight(): # func to determin whether the Change weight led will light up or not
    global ChangeWeight
    if (ChangeWeight == True):
        changeWeightLed.config(bg = "green")
    else:
        changeWeightLed.config(bg = "black")

        
#enter pressed**************************************************Enter Pressed******************************************
        
def EnterPressed():
    global ChangeTime
    global keyOut
    global Clear
    if(ChangeTime == True):
        KeyOutToTimeIn(keyOut) #start the keyOut to time func
        ChangeTimeFunc() #deactivate the change time func
    if (ChangeWeight == True):
        WeightDisp.config(text = keyOut)#change the weight class text
        WeightChange()#deactivate the change weight func
    if(ChangeBout == True):
        BoutDisp.config(text = keyOut)
        BoutChange()
    clear = True #clear the key pad Display
    keyInput("no") #run the key pad func to set clear into effect

#easy/quick time changefunctions
def timeSubSec():
    global TimeIn
    TimeIn = TimeIn - 100
    TimeDispConfig(TimeIn)
    return TimeIn

def timeAddSec():
    global TimeIn
    TimeIn = TimeIn + 100
    TimeDispConfig(TimeIn)
    return TimeIn

    #scores

def greenAdd():
    global greenScore
    greenScore = greenScore + 1
    greenDisp()
    return greenScore



def greenSub():
    global greenScore
    if (greenScore != 0):
        greenScore = greenScore - 1
        greenDisp()
    return greenScore

def redAdd():
    global redScore
    redScore = redScore + 1 
    redDisp()
    return redScore


def redSub():
    global redScore
    if (redScore != 0):
        redScore = redScore - 1
        redDisp()
    return redScore


#buttons
    #time
StartBtn = Button(frame, bg = "green", text = "Start\n (space)", fg="White", command = StartPressed)
StartBtn.place(height=40, width=170, y=100, x=425)
#binding for start btn
def ExtStart(event):
    StartPressed()
    
win.bind("<space>", ExtStart)
#change time digital btn
changeTimeBtn = Button(frame, bg = "blue", text = "changeTime\n (Insert)", fg="White", command = ChangeTimeFunc)
changeTimeBtn.place(height=40, width=170, y=150, x=425)
#change time external btn
def ExtChangeTime(event):
    ChangeTimeFunc()
    
win.bind("<Insert>", ExtChangeTime)

    #change time easy
time1 = Button(frame, bg = "red", text = "-1", fg="White", command = timeSubSec)
time1.place(height=40, width=40, y=50, x=610)

time2 = Button(frame, bg = "green", text = "+1", fg="White", command = timeAddSec)
time2.place(height=40, width=40, y=10, x=610)
#binding the change time easy external btns


    #Change Bout and change Weight Buttons
WeightBtn = Button(frame, bg = "blue", text = "Change Weight Class\n (Home)", fg="White", command = WeightChange)
WeightBtn.place(height=40, width=170, y=450, x=425)

BoutBtn = Button(frame, bg = "blue", text = "Change Bout Number\n (Pg Up)", fg="White", command = BoutChange)
BoutBtn.place(height=40, width=170, y=300, x=425)

#Change bout and weight btn bindings
def ExtBout(event):
    BoutChange()

def ExtWeight(event):
    WeightChange()

win.bind("<Home>", ExtBout)
win.bind("<Prior>", ExtWeight)
    #score
green1 = Button(frame, bg = "red", text="-1\n (a)", fg="White", command = greenSub)
green1.place(height=40, width=70, y=200, x=125)


green2 = Button(frame, bg = "green", text="+1\n (q)", fg="White", command = greenAdd)
green2.place(height=40, width=70, y=200, x=225)

red1 = Button(frame, bg = "red", text="-1\n (l)", fg="White", command = redSub)
red1.place(height=40, width=70, y=200, x=725)


red2 = Button(frame, bg = "green", text="+1\n (p)", fg="White", command = redAdd)
red2.place(height=40, width=70, y=200, x=825)
#bindings for score changing btns
def ExtGreen1(event):
    greenSub()

def ExtGreen2(event):
    greenAdd()

def ExtRed1(event):
    redSub()

def ExtRed2(event):
    redAdd()

win.bind("<a>", ExtGreen1)
win.bind("<q>", ExtGreen2)
win.bind("<l>", ExtRed1)
win.bind("<p>", ExtRed2)
    #keypad buttons
Key1 = Button(frame, bg = "grey", text = "1", fg="White", command = keyPad1)
Key1.place(height=40, width=40, y=450, x=50)

Key2 = Button(frame, bg = "grey", text = "2", fg="White", command = keyPad2)
Key2.place(height=40, width=40, y=450, x=90)

Key3 = Button(frame, bg = "grey", text = "3", fg="White", command = keyPad3)
Key3.place(height=40, width=40, y=450, x=130)

Key4 = Button(frame, bg = "grey", text = "4", fg="White", command = keyPad4)
Key4.place(height=40, width=40, y=490, x=50)

Key5 = Button(frame, bg = "grey", text = "5", fg="White", command = keyPad5)
Key5.place(height=40, width=40, y=490, x=90)

Key6 = Button(frame, bg = "grey", text = "6", fg="White", command = keyPad6)
Key6.place(height=40, width=40, y=490, x=130)

Key7 = Button(frame, bg = "grey", text = "7", fg="White", command = keyPad7)
Key7.place(height=40, width=40, y=530, x=50)

Key8 = Button(frame, bg = "grey", text = "8", fg="White", command = keyPad8)
Key8.place(height=40, width=40, y=530, x=90)

Key9 = Button(frame, bg = "grey", text = "9", fg="White", command = keyPad9)
Key9.place(height=40, width=40, y=530, x=130)

Key0 = Button(frame, bg = "grey", text = "0", fg="White", command = keyPad0)
Key0.place(height=40, width=40, y=570, x=90)
#Break*******************************
keyClear = Button(frame, bg = "red", text = "clear\n (+)", fg="White", command = clearKey)#btn that clears the num input field
keyClear.place(height=40, width=40, y=570, x=50)

keyEnter = Button(frame, bg = "green", text = "Enter\n (Enter)", fg="White", command = EnterPressed)#btn that inserts the input field into the the selected spot
keyEnter.place(height=40, width=40, y=570, x=130)
# bindings for external btns for enter and clear
def ExtEnter(event):#middle btn for the Enter func and the binding
    EnterPressed()

def ExtClear(event):#middle btn for the Clear func and the binding
    clearKey()

win.bind("<Return>", ExtEnter)
win.bind("<Key-+>", ExtClear)
#start windows event loop
win.mainloop()

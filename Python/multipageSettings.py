import tkinter
from tkinter import*
import ctypes#try to utilize***************************************************************************************************************************************************
#creating the window
win = tkinter.Tk()

#modify the window
win.title("REFtech settings")#creating the main window
win.geometry("400x600")#Setting the size

#create base frames
frame = Frame(win, bg="Black")#creating the background frame
frame.place(height=600, width=400, x=0, y=0)#placeing it 

onload = Frame(frame, height=350, width=380, bg="Grey")#create the onload page frame
onload.place( x=10, y=40)

Settings = Frame(frame, bg="Grey")#create the Settings frame
Settings.place(x=10, y=40)
Settings.config(height=0, width=0)

FirstCon = Frame(frame, bg ="Grey")
FirstCon.place(x=10, y=40)
FirstCon.config(width = 0, height = 0)

changeName = Frame(frame, bg ="Grey")
changeName.place(x=10, y=40)
changeName.config(width = 0, height = 0)

#testing***************************testing**************

#contents of onload frame****************************BREAK***********************8
PressEnterTXT = Label(onload, width = 40, height= 10, bg = "grey", fg = "white", text = "Press Enter to continue", font=30)#creating the text  
PressEnterTXT.place(x=10, y=80)#placing it

flashValue = True
flashInt = 1
def  FlashingTxt():
    global flashInt #number of times this function ran
    global flashValue # whether the function shoul run or not
    flashInt = flashInt + 1 #adds one every time this function runs
    if(flashInt%2 == 0):
        PressEnterTXT.config(fg = "grey")#hides the text
    else:
        PressEnterTXT.config( fg = "white")#shows the text
    if (flashValue == True):
        win.after(500, FlashingTxt)#repeat function every half second
    else:
        PressEnterTXT.config(fg = "grey")#hides the text
FlashingTxt()#initialy starts the function



#contents of Settings frame****************************BREAK***********************
ChangeNameBtn = Button(Settings, width = 12, height = 2, bg = "white", fg="black", text = "Change Name")#adding the connect button to the Settings frame
ChangeNameBtn.place(x=20, y = 70)
ChangeNameBtnLoc = 1, 1

GenBtn = Button(Settings, width = 12, height = 2, bg = "white", fg="black", text = "General Settings")#adding the connect button to the Settings frame
GenBtn.place(x=120, y = 70)
GenBtnLoc = 1, 2

UnknowBtn = Button(Settings, width = 12, height = 2, bg = "white", fg="black", text = "Unknown")#adding the connect button to the Settings frame
UnknowBtn.place(x=220, y = 70)
UnknowBtnLoc = 1, 3

ConnectBtn = Button(Settings, width = 12, height = 2, bg = "white", fg="black", text = "Connect")#adding the connect button to the Settings frame
ConnectBtn.place(x=20, y = 270)
ConBtnLoc = 2, 1

ChangeBtn = Button(Settings, width = 12, height = 2, bg = "white", fg="black", text = "Change")#adding the connect button to the Settings frame
ChangeBtn.place(x=120, y = 270)
ChaBtnLoc = 2, 2

GenSetBtn = Button(Settings, width = 12, height = 2, bg = "white", fg="black", text = "Settings")#adding the connect button to the Settings frame
GenSetBtn.place(x=220, y = 270)
GenSetBtnLoc = 2, 3
#contents of change name page**************************************************************break*********************
Name = "default"
NameInput = Entry(changeName, bd = 5, exportselection=0, textvariable = Name)
NameInput.place(x=175, y=190)
def checkName():
    global Name
    Name = NameInput.get()
    print (Name)
ChangeNameEnter = Button(changeName, width = 5, height = 2, bg = "white", fg = "black", text = "Enter", command = checkName)
ChangeNameEnter.place(x=40, y= 50)

changeNameBack = Button(changeName, width = 8, height = 2, bg = "white", fg = "black", text = "Back"  )          
#contents of First connect page *************************************************Break******************

    #creating the label
rolling = Label(FirstCon, bg = "grey", fg = "white", width = 43, text = "hello", font = 30)
rolling.place(x=0, y=155)

#create the canvas
canTop = Canvas (FirstCon, bd = 0, height = 0, width = 380)
canTop. place(y=170, x=0)

canBot = Canvas (FirstCon, bd = 0, height = 0, width = 380)
canBot. place(y=200, x=0)
    #the actual function
devFoundNum = 3
devFound = "Device_1" "\n" "\n" "\n" "Device_2" "\n" "\n" "\n" "Device_3"
rollInt = 1

def selecting():
    global devFound
    global rollInt
    global devFoundNum
    posRoll = rollInt * 50 - 50
    rollingHeight = devFoundNum * 5
    rolling.config(height = rollingHeight, text = devFound)
    print(rollInt)
    rolling.place(y=posRoll)
    

selecting()

#PAGE functions
Frame = "Onload"

MaxRow = 0
MaxCol = 0

def onloadFunc():# function that sets page value
    global Frame
    Frame = "Onload"
    AllPageFunction(Frame)

def SettingsPageFunc():# function that sets page value
    global Frame
    Frame = "Settings"
    AllPageFunction(Frame)

def FirstConectFunc():#func that sets the page value to the 1st connect Page
    global Frame
    Frame = "FirstCon"
    AllPageFunction(Frame)

def changeNameFunc():#func that sets the page value to change name
    global Frame
    Frame = "changeName"
    ChangeNameBtn.invoke()
    
def AllPageFunction(frameIn): #creating the function that opens the frame for the current page
    global Frame
    global MaxRow
    global MaxCol
    if (frameIn == "Onload"):
        onload.config(height=350, width=380)
    else:
        onload.config(height=0, width=0)
    if (frameIn == "Settings"):
        Settings.config(height=350, width=380)
        MaxRow = 3
        MaxCol = 2
    else:
        Settings.config(height=0, width=0)
    if(frameIn == "FirstCon"):
        FirstCon.config(height = 350, width = 380)
        MaxRow = 3
        MaxCol = 1
    else:
        FirstCon.config(height = 0, width = 0)
    if(frameIn == "changeName"):
        changeName.config( height = 350, width = 380)
        MaxRow = 3
        MaxCol = 1
    else:
        changeName.config(width = 0, height = 0)
onloadFunc()#sets the initial page

#creating the functions for the buttons
RowInt = 1
ColInt = 1
def hover(obj):#the func that changes color of the btns
    obj.config(bg = "grey")

def norm(obj):
    obj.config(bg = "White")

Loc = 0
def findLoc():#determing witch btn is being hovered over
    global RowInt
    global ColInt
    global Frame
    global ConBtnLoc
    global ChaBtnLoc
    global GenSetBtnLoc
    global ChangeNameBtnLoc
    global GenBtnLoc
    global UnknowBtnLoc
    global Loc
    Loc = ColInt, RowInt
    #settings page************
    if(ChangeNameBtnLoc == Loc):
        hover(ChangeNameBtn)
    else:
        norm(ChangeNameBtn)
    #****
    if(GenBtnLoc == Loc):
        hover(GenBtn)
    else:
        norm(GenBtn)
    #****
    if(UnknowBtnLoc == Loc):
        hover(UnknowBtn)
    else:
        norm(UnknowBtn)
    #****
    if(ConBtnLoc == Loc):
        hover(ConnectBtn)
    else:
        norm(ConnectBtn)
    #****
    if(ChaBtnLoc == Loc):
        hover(ChangeBtn)
    else:
        norm(ChangeBtn)
    #****
    if(GenSetBtnLoc == Loc):
        hover(GenSetBtn)
    else:
        norm(GenSetBtn)
    print(Loc)

#Enter Pressed ****************************** Enter ***************************   
def EnterPressed():#controls what happens when the enter butten is pressed
    global flashValue
    global Frame
    
    if (Frame == "Onload"):#hides the first frame, the onload frame
        flashValue = False
        Frame = "Settings"
    AllPageFunction(Frame)
    if (Frame == "Settings"):
        print("hello")
        if(ConBtnLoc == Loc):
            FirstConectFunc()
        if(ChangeNameBtnLoc == Loc):
            changeNameFunc()
        

    
#Enter Pressed ****************************** Enter ***************************   

    
def AddRow():#Adds to the row in when right btn is clicked
    global MaxRow
    global RowInt
    if(MaxRow > RowInt):#makes sure that the row int cant go higher than the max row int set for that page
        RowInt = RowInt + 1
    findLoc()
def SubRow(): #Subs from the row int when the left btn is clicked
    global RowInt
    if(1<RowInt):#makes sure that the row int can't be less than 1
        RowInt = RowInt - 1
    findLoc()

def AddCol():#adds to the Col int when the down btn is clicked
    global MaxCol
    global ColInt
    global Frame
    global devFoundNum
    global rollInt
    if(Frame == "Settings"):
        if(MaxCol > ColInt):#makes sure that the col int cant go higher than the amount of cols that the page has
            ColInt = ColInt + 1
        findLoc()
    if(Frame == "FirstCon"):
        if(1 < rollInt):
            rollInt = rollInt - 1
        selecting()
    
def SubCol(): #adds to the Col int when the down btn is clicked
    global ColInt
    global Frame
    global rollInt
    if(Frame == "Settings"):
        if(1<ColInt):#makes sure that the col int cant be less than 1
            ColInt = ColInt - 1
        findLoc()
    if(Frame == "FirstCon"):
        if(devFoundNum > rollInt):
            rollInt = rollInt + 1
        selecting()

#create the digital buttons later to be converted into analog
upBtn = Button(frame, text = "Up", bg = "grey", fg = "white", command = SubCol)
upBtn.place(x=10, y=460, width = 190, height = 50)

DownBtn = Button(frame, text = "Down", bg = "grey", fg = "white", command = AddCol)
DownBtn.place(x=200, y=460, width = 190, height = 50)

LeftBtn = Button(frame, text = "Left", bg = "grey", fg = "white", command = SubRow)
LeftBtn.place(x=10, y=410, width = 190, height = 50)

RightBtn = Button(frame, text = "Right", bg = "grey", fg = "white", command = AddRow)
RightBtn.place(x=200, y=410, width = 190, height = 50)

EnterBtn = Button(frame, text = "Enter", bg = "grey", fg = "white", command = EnterPressed)
EnterBtn.place(x=10, y=510, width = 380, height = 50)

#create main loop
win.mainloop()

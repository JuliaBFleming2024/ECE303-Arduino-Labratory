import serial
import time
import tkinter as tk
import tkinter.font as tkFont
from tkinter import *
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

plt.close('all')
root = tk.Tk()
root.geometry("1000x600")
root.title("Photoresistor Evaluator")
root.configure(bg='grey')

figure1 = plt.Figure(figsize=(12, 6), dpi=100)
ax1 = figure1.add_subplot(221)
fig1 = FigureCanvasTkAgg(figure1, root)
fig1.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH)
figure1.set_facecolor('lightgrey')
line1, = ax1.plot([], [], 'bo')
ax1.set_xlabel('Duty Cycle (%)', fontsize=10)
ax1.set_ylabel('Voltage (V)', fontsize=10)
ax1.set_title('Photocell Voltage')
ax1.grid(True, which='major', color='k', linestyle='-')
ax1.grid(True, which='minor', color='r', linestyle='-', alpha=0.2)
ax1.minorticks_on()

ax2 = figure1.add_subplot(223)
line2, = ax2.plot([], [], 'bo')
ax2.set_xlabel('Duty Cycle (%)', fontsize=10)
ax2.set_ylabel('Current (mA)', fontsize=10)
ax2.set_title('Photocell Current')
ax2.grid(True, which='major', color='k', linestyle='-')
ax2.grid(True, which='minor', color='r', linestyle='-', alpha=0.2)
ax2.minorticks_on()

ax3 = figure1.add_subplot(224)
line3, = ax3.plot([], [], 'bo')
ax3.set_xlabel('Duty Cycle (%)', fontsize=10)
ax3.set_ylabel('Resistance', fontsize=10)
ax3.set_title('Photocell Resistance')
ax3.grid(True, which='major', color='k', linestyle='-')
ax3.grid(True, which='minor', color='r', linestyle='-', alpha=0.2)
ax3.minorticks_on()

figure1.subplots_adjust(hspace=0.5)

fontStyle = tkFont.Font(family="Lucida Grande", size=14)
var = StringVar()
label = Label(root, textvariable=var, font=fontStyle, bg='Lightgrey')
label.place(x=50, y=500)

def startCallBack():
    arduino = serial.Serial('/dev/cu.usbmodem101', 9600, timeout=5)
    time.sleep(1)
    DC = []
    V_res = []
    V_pc = []
    I = []
    R = []
    for i in range(1, 255):
        arduino.reset_input_buffer()
        arduino.reset_output_buffer()
        DC.append(i/255*100)
        var.set("Duty Cycle: {:.2f} %".format(DC[-1]))
        time.sleep(0.01)
        arduino.write(b'1')
        time.sleep(0.5)
        a = int(arduino.read(4).decode("ascii"))
        V_res.append(a/1023*5)
        V_pc.append(V_res[-1]/5000*1000)
        R.append(V_pc[-1]/I[-1])

        line1.set_data(DC, V_pc)
        axa = fig1.figure.axes[0]
        axa.set_xlim(0, 100)
        axa.set_ylim(0, 5)

        line2.set_data(DC, I)
        axb = fig1.figure.axes[1]
        axb.set_xlim(0, 100)
        axb.set_ylim(0, 1)

        line3.set_data(DC, R)
        axc = fig1.figure.axes[2]
        axc.set_xlim(0, 100)
        axc.set_ylim(0, 250)

        fig1.draw()
        plt.pause(0.05)

    arduino.close()

startButton = Button(root, text="START", command=startCallBack)
startButton.place(x=33, y=28)

root.mainloop()

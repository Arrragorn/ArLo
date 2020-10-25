#!/usr/bin/env python
# coding: utf-8



import sys




import tkinter as tk
from tkinter.filedialog import askopenfilename





sys.path.append(".")




import spam









def handl_quit():
    spam.quit()
    fenetre.destroy()
                    
def handl_run():
    filename = askopenfilename()
    spam.run(filename)


fenetre = tk.Tk()
greeting = tk.Label(text="Hello, Tkinter")
greeting.pack()

run_button = tk.Button(text="run", fg="black",command=handl_run)
run_button.pack( side = tk.LEFT)


replay_button = tk.Button(text="replay", fg="black",command=spam.replay)
replay_button.pack( side = tk.LEFT)



play_button = tk.Button(text="play", fg="black",command=spam.play)
play_button.pack( side = tk.LEFT)

pause_button = tk.Button(text="pause", fg="black",command=spam.pause)
pause_button.pack( side = tk.LEFT)

accelerate1x_button = tk.Button(text="1x", fg="black",command=spam.accelerate1x)
accelerate1x_button.pack( side = tk.LEFT)

accelerate2x_button = tk.Button(text="2x", fg="black",command=spam.accelerate2x)
accelerate2x_button.pack( side = tk.LEFT)



fenetre.protocol("WM_DELETE_WINDOW", handl_quit)
fenetre.mainloop()




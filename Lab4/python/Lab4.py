#!/usr/bin/env python
# coding: utf-8

# In[1]:


import sys
import threading
import time
import multiprocessing as mp


# In[2]:


import tkinter as tk
    



# In[4]:


sys.path.append(".")
import boucleThread


# In[5]:


def boucle_interprete_thread(n_iter,n_thread):
    pool = mp.Pool()
    pool.map(boucle_interprete_simple,[int(n_iter/n_thread)]*n_thread)
    
    
def wapper_boucle_interprete_thread():
    time_init = time.perf_counter()
    boucle_interprete_thread(int(v_iteration.get()),4)
    v_temps.set(str(time.perf_counter() - time_init))


# In[7]:


def boucle_interprete_simple(n_iter):
    for i in range(n_iter):
        pass
def wapper_boucle_interprete_simple():
    time_init = time.perf_counter()
    boucle_interprete_simple(int(v_iteration.get()))
    v_temps.set(str(time.perf_counter() - time_init))


# In[8]:


def wapper_boucle_compile_simple():
    time_init = time.perf_counter()
    boucleThread.boucleSimple(int(v_iteration.get()))
    v_temps.set(str(time.perf_counter() - time_init))


# In[9]:


def wapper_boucle_compile_thread():
    time_init = time.perf_counter()
    boucleThread.boucleThread(int(v_iteration.get()))
    v_temps.set(str(time.perf_counter() - time_init))


# In[ ]:





# In[10]:

if __name__ == "__main__":

    fenetre = tk.Tk()
    
   
    
    greeting = tk.Label(text="Hello, Tkinter")
    greeting.pack(side = tk.TOP)
    
    
    label_nb_itration = tk.Label(text="inserer nb iterations")
    label_nb_itration.pack(side = tk.LEFT)
    
    v_iteration = tk.StringVar()
    entry_nb_iteration = tk.Entry(textvariable=v_iteration)
    entry_nb_iteration.pack(side = tk.LEFT)
    
    
    label_consume = tk.Label(text="temps consume:")
    label_consume.pack(side = tk.LEFT)
    
    v_temps = tk.StringVar()
    label_temps = tk.Label(textvariable=v_temps)
    label_temps.pack(side = tk.LEFT)
    v_temps.set("^&^")
    
    interprete_simple_button = tk.Button(text="interprete simple", fg="black",command=wapper_boucle_interprete_simple)
    interprete_simple_button.pack( side = tk.BOTTOM)
    
    interprete_thread_button = tk.Button(text="interprete thread", fg="black",command=wapper_boucle_interprete_thread)
    interprete_thread_button.pack( side = tk.BOTTOM)
    
    compile_simple_button = tk.Button(text="compile simple", fg="black",command=wapper_boucle_compile_simple)
    compile_simple_button.pack( side = tk.BOTTOM)
    
    
    compile_thread_button = tk.Button(text="compile thread", fg="black",command=wapper_boucle_compile_thread)
    compile_thread_button.pack( side = tk.BOTTOM)
    
    
    fenetre.mainloop()


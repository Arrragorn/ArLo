#!/usr/bin/env python
# coding: utf-8

# In[1]:


import sys
import time


# In[2]:


sys.path.append(".")


# In[3]:


import boucleThread


# In[6]:


time_init = time.perf_counter()
boucleThread.boucleSimple(1000000)
print( time.perf_counter() - time_init)


# In[7]:


time_init = time.perf_counter()
boucleThread.boucleThread(1000000)
print( time.perf_counter() - time_init)


# In[ ]:





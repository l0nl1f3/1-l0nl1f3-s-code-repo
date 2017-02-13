#coding=utf-8
from tkinter import *
from tkinter import ttk
from tkinter import filedialog
from tkinter import messagebox
import interface
import os
import json

tk=Tk()
tk.title('JudgeLight')
tk.attributes('-toolwindow',True)
tk.attributes('-topmost',True)
tk.resizable(False,False)

judger=None
sourcefn=None
msg=StringVar()
msg.set('Please fill in your OJ info.')

def config():
    sub=Toplevel(tk)
    sub.title('Config - JudgeLight')
    
    sub.columnconfigure(1,weight=1)
    sub.rowconfigure(2,weight=1)

    def goback(*_):
        tk.attributes('-alpha',1)
        sub.destroy()
    tk.attributes('-alpha',0)
    sub.protocol('WM_DELETE_WINDOW',goback)

    filename=None
    oj=None
    ojnamevar=StringVar()
    submsg=StringVar()
    submsg.set('Please select file.')

    def selectfile():
        fnin=filedialog.askopenfilename(filetypes=(('C++ Source Code','*.cpp'),))
        if fnin and os.path.isfile(fnin):
            filenamebtn['text']=fnin
            nonlocal filename
            filename=fnin
            submsg.set('File selected.')
            savebtn['state']='normal'

    def updatedefault(*_):
        ojname=ojnamebox.get()
        if ojname in interface.valid_ojs.keys():
            configin.delete(1.0,END)
            configin.insert(END,interface.valid_ojs[ojname].default_var)
            nonlocal oj
            oj=interface.valid_ojs[ojname]
        else:
            msgvar.set('No such OJ.')

    def save():
        def callback(s):
            submsg.set(s)
            sub.update()
        try:
            config=json.loads(configin.get(1.0,END))
        except ValueError:
            submsg.set('Invalid OJ Config.')
            return
        try:
            oj_instance=oj(callback,config)
        except interface.Error as e:
            submsg.set('Error: %s'%e)
        except Exception as e:
            submsg.set('Uncaught Error: %r'%e)
        else:
            judgebtn['state']='normal'
            global judger
            judger=oj_instance
            global sourcefn
            sourcefn=filename
            goback()
            tk.title('JudgeLight [ %s ]'%os.path.basename(filename))
            msg.set('Ready.')
            sub.destroy()

    Label(sub,text='Source Code').grid(row=0,column=0)
    filenamebtn=ttk.Button(sub,text='Select File...',command=selectfile)
    filenamebtn.grid(row=0,column=1,sticky='WE')

    Label(sub,text='OJ Type').grid(row=1,column=0)
    ojnamebox=ttk.Combobox(sub,textvariable=ojnamevar,\
        values=tuple(interface.valid_ojs.keys()))
    ojnamebox.grid(row=1,column=1,sticky='WE')
    ojnamebox.bind('<<ComboboxSelected>>',updatedefault)

    Label(sub,text='OJ Config').grid(row=2,column=0)
    configin=Text(sub,height=10)
    configin.grid(row=2,column=1,sticky='WE')

    savebtn=ttk.Button(sub,text='Save',command=save,state='disabled')
    savebtn.grid(row=3,column=0,sticky='WE')
    Label(sub,textvariable=submsg).grid(row=3,column=1)

def judge():
    def callback(s):
        msg.set(s)
        tk.update()

    judgebtn['state']='disabled'
    cfgbtn['state']='disabled'
    tk.update()
    
    try:
        with open(sourcefn,'r') as f:
            source=f.read()
    except Exception as e:
        msg.set('Cannot read source code: %r'%e)

    try:
        judger.update(callback,source)
    except interface.Error as e:
        msg.set(e)
    except Exception as e:
        msg.set('Uncaught Error: %r'%e)

    judgebtn['state']='normal'
    cfgbtn['state']='normal'

cfgbtn=ttk.Button(tk,text='Config',command=config,width=7)
cfgbtn.grid(row=0,column=0,padx=2)
judgebtn=ttk.Button(tk,text='Judge!',width=10,command=judge,state='disabled')
judgebtn.grid(row=0,column=1,padx=2,pady=2)

Label(tk,textvariable=msg).grid(row=0,column=2,padx=3)

mainloop()

# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'projectFOTA.ui'
##
## Created by: Qt User Interface Compiler version 5.14.0
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide2.QtCore import (QCoreApplication, QMetaObject, QObject, QPoint,
    QRect, QSize, QUrl, Qt, QTimer)
from PySide2.QtGui import (QBrush, QColor, QConicalGradient, QFont,
    QFontDatabase, QIcon, QLinearGradient, QPalette, QPainter, QPixmap,
    QRadialGradient)
from PySide2.QtWidgets import *
import re
import sys
from google.cloud import storage
import os 
import time
import xml.dom.minidom
import xml.etree.ElementTree as ET
import threading
from tkinter.commondialog import Dialog
from elftools.elf.elffile import ELFFile , Segment
from elftools.elf.structs import ELFStructs
import tkinter as tk
from tkinter import messagebox


jsonFile='fotaproject40-31b13f58a47b.json'
class Ui_Form(object):
    counter=0
    def setupUi(self, Form):
        if Form.objectName():
            Form.setObjectName(u"Form")
        Form.resize(896, 563)
        self.pushButton = QPushButton(Form)
        self.pushButton.setObjectName(u"pushButton")
        self.pushButton.setGeometry(QRect(370, 10, 111, 51))
        self.textEdit = QTextEdit(Form)
        self.textEdit.setObjectName(u"textEdit")
        self.textEdit.setGeometry(QRect(20, 10, 321, 51))
        self.textEdit.setStyleSheet(u"background-color: white;\n"
"font: 10pt \"MS Shell Dlg 2\";\n"
"")
        self.pushButton_2 = QPushButton(Form)
        self.pushButton_2.setObjectName(u"pushButton_2")
        self.pushButton_2.setGeometry(QRect(370, 80, 111, 51))
       #self.comboBox = QComboBox(Form)
       #self.comboBox.addItem(u"STM32F103")
       #self.comboBox.addItem(u"TivaC")
       #self.comboBox.addItem(u"ATMEGA32")
       #self.comboBox.setObjectName(u"comboBox")
       #self.comboBox.setGeometry(QRect(110, 80, 171, 31))
        
        #self.label_2 = QLabel(Form)
        #self.label_2.setObjectName(u"label_2")
        #self.label_2.setGeometry(QRect(20, 70, 101, 41))
        #self.label_2.setStyleSheet(u"font: 11pt \"MS Shell Dlg 2\";")
        self.label_3 = QLabel(Form)
        self.label_3.setObjectName(u"label_3")
        self.label_3.setGeometry(QRect(50, 80, 271, 121))
        self.label_3.setStyleSheet(u"color: rgb(0, 0, 127);\n"
"font: 20pt \"Britannic Bold\";")
        self.label_4 = QLabel(Form)
        self.label_4.setObjectName(u"label_4")
        self.label_4.setGeometry(QRect(620, 60, 331, 51))
        self.label_4.setStyleSheet(u"color: rgb(0, 0, 127);\n"
"font: 28pt \"Britannic Bold\";\n"
"")
        self.label = QLabel(Form)
        self.label.setObjectName(u"label")
        self.label.setGeometry(QRect(30, 180, 841, 381))
        self.label.setPixmap(QPixmap(u"image/FOTAimg.jpg"))
        self.pushButton_3 = QPushButton(Form)
        self.pushButton_3.setObjectName(u"pushButton_3")
        self.pushButton_3.setGeometry(QRect(100, 70, 171, 41))
        
        self.comboBox_2 = QComboBox(Form)   
        self.comboBox_2.addItem(u"verna_2018")
        self.comboBox_2.addItem(u"elantra_2019")
        self.comboBox_2.addItem(u"sunny_2020")       
        self.comboBox_2.setObjectName(u"comboBox_2")
        self.comboBox_2.setGeometry(QRect(520, 40, 101, 22))
        self.comboBox_3 = QComboBox(Form)
        self.comboBox_3.setObjectName(u"comboBox_3")
        self.comboBox_3.setGeometry(QRect(650, 40, 101, 22))
        self.comboBox_4 = QComboBox(Form)
        self.comboBox_4.setObjectName(u"comboBox_4")
        self.comboBox_4.setGeometry(QRect(790, 40, 101, 22))

        client = storage.Client.from_service_account_json(jsonFile)
        bucket = client.get_bucket('fotaproject_bucket')
        blob7 = bucket.blob("cars_ids.xml")
        blob7.download_to_filename("cars_ids.xml")
        tree = ET.parse("cars_ids.xml")
        root = tree.getroot()        
        self.comboBox_4.addItem(u"STM32F103-1")
        self.comboBox_4.addItem(u"TivaC-1")
        idx=0
        tags =  [elem.tag for elem in root.iter()] 
        attrs = [elem.text for elem in root.iter()]        
        for i in tags:
          x=re.search(r'verna_2018.+',i)
          if x and attrs[idx] == "available":  
            self.comboBox_3.addItem(x.group())
          idx+=1        
        
        self.label_8 = QLabel(Form)
        self.label_8.setObjectName(u"label_5")
        self.label_8.setGeometry(QRect(540, 10, 61, 21))
        self.label_6 = QLabel(Form)
        self.label_6.setObjectName(u"label_6")
        self.label_6.setGeometry(QRect(680, 10, 61, 21))
        self.label_7 = QLabel(Form)
        self.label_7.setObjectName(u"label_7")
        self.label_7.setGeometry(QRect(810, 10, 71, 21))
        
        self.progressBar = QProgressBar(Form)
        self.progressBar.setObjectName(u"progressBar")
        self.progressBar.setGeometry(QRect(615, 137, 241, 26))
        #self.progressBar.setValue(0)
        self.label_5 = QLabel(Form)
        self.label_5.setObjectName(u"label_5")
        self.label_5.setGeometry(QRect(510, 130, 111, 31))
        self.label_5.setStyleSheet(u"font: 11pt \"MS Shell Dlg 2\";")

        self.retranslateUi(Form)

        QMetaObject.connectSlotsByName(Form)
    # setupUi

    def retranslateUi(self, Form):
        Form.setWindowTitle(QCoreApplication.translate("Form", u"Form", None))
        self.pushButton.setText(QCoreApplication.translate("Form", u"BROWSE", None))
        self.pushButton.clicked.connect(self.pushButton_handler)
        self.comboBox_2.activated.connect(self.car_model_change)
        self.textEdit.setHtml(QCoreApplication.translate("Form", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", None))
        self.pushButton_2.setText(QCoreApplication.translate("Form", u"UPLOAD", None))
        self.pushButton_2.clicked.connect(self.pushButton_handler2)
        self.comboBox_2.setItemText(0, QCoreApplication.translate("Form", u"verna_2018", None))
        self.comboBox_2.setItemText(1, QCoreApplication.translate("Form", u"elantra_2019", None))
        self.comboBox_2.setItemText(2, QCoreApplication.translate("Form", u"sunny_2020", None))

        #a = self.comboBox_2.currentText()
      

        #self.label_2.setText(QCoreApplication.translate("Form", u"Target :", None))
        self.label_3.setText(QCoreApplication.translate("Form", u"Firmware Over The Air", None))
        #self.label_4.setText(QCoreApplication.translate("Form", u"FOTA", None))
        self.label.setText("")
        self.pushButton_3.setText(QCoreApplication.translate("Form", u"CHECK FLASHING STATUS", None))
        self.pushButton_3.clicked.connect(self.pushButton_handler3)
        self.label_8.setText(QCoreApplication.translate("Form", u"Car's Model", None))
        self.label_6.setText(QCoreApplication.translate("Form", u"Car's ID", None))
        self.label_7.setText(QCoreApplication.translate("Form", u"Car's Target", None))
        self.label_5.setText(QCoreApplication.translate("Form", u"Status ", None))
        self.timer = QTimer()      
        self.timer.timeout.connect(self.handleTimer)

   
    # retranslateUi
    
    
    def car_model_change(self):
      try:
        client = storage.Client.from_service_account_json(jsonFile)
        bucket = client.get_bucket('fotaproject_bucket')
        blob7 = bucket.blob("cars_ids.xml")
        blob7.download_to_filename("cars_ids.xml")
        tree = ET.parse("cars_ids.xml")
        root = tree.getroot()
        idx=0
        tags =  [elem.tag for elem in root.iter()]
        attrs = [elem.text for elem in root.iter()]
        self.comboBox_4.clear()
        if self.comboBox_2.currentText() == "verna_2018":
          self.comboBox_4.addItem(u"STM32F103-1")
          self.comboBox_4.addItem(u"TivaC-1")
          self.comboBox_3.clear()
          for i in tags:
            x=re.search(r'verna_2018.+',i)
            if x and attrs[idx] == "available":  
              self.comboBox_3.addItem(x.group())
              self.comboBox_3.setItemText(0, QCoreApplication.translate("Form", x.group(), None))
            idx+=1  
        if self.comboBox_2.currentText() == "elantra_2019":
          self.comboBox_4.addItem(u"STM32F103-1")
          self.comboBox_4.addItem(u"ATMEGA32-1")      
          self.comboBox_3.clear()
          for i in tags:
            x=re.search(r'elantra_2019.+',i)
            if x and attrs[idx] == "available":  
              self.comboBox_3.addItem(x.group())
              self.comboBox_3.setItemText(0, QCoreApplication.translate("Form", x.group(), None))
            idx+=1  
        if self.comboBox_2.currentText() == "sunny_2020":
          self.comboBox_4.addItem(u"STM32F103-1")
          self.comboBox_4.addItem(u"ATMEGA32-1")  
          self.comboBox_4.addItem(u"TivaC-1")        
          self.comboBox_3.clear()
          for i in tags:
            x=re.search(r'sunny_2020.+',i)
            if x and attrs[idx] == "available":  
              self.comboBox_3.addItem(x.group()) 
              self.comboBox_3.setItemText(0, QCoreApplication.translate("Form", x.group(), None))              
            idx+=1  
      except Exception as ex:
        msg9 = QMessageBox()
        msg9.setWindowTitle("Warning")
        msg9.setText("Failed Connecting to server for downloading the car ids xml file !                ")
        msg9.setIcon(QMessageBox.Warning)
        y=msg9.exec_()    
    
    def pushButton_handler(self):
        self.textEdit.clear()
        print("Button pressed")
        self.open_dialog_box()
   
    def open_dialog_box(self):
        fileName = QFileDialog.getOpenFileName()
        self.path = fileName[0]
        #field = QtGui.extEdit()
        
        if os.path.isfile(self.path) or self.textEdit.toPlainText() != "":
          self.textEdit.setText(self.path)
          print(os.path.basename(self.path))
          x=self.verify_Elf_File()
          print(x)
          if os.path.basename(self.path).endswith('.elf') and  self.verify_Elf_File() :
            self.pushButton_2.setEnabled(True)
          else:
            self.pushButton_2.setEnabled(False)
            msgF = QMessageBox()
            msgF.setWindowTitle("Warning")
            msgF.setText("Please Choose an .elf File for uploading !                 ")
            msgF.setIcon(QMessageBox.Warning)
            y=msgF.exec_()
        else :
          self.pushButton_2.setEnabled(False)
          msg2 = QMessageBox()
          msg2.setWindowTitle("Warning")
          msg2.setText("Please Choose a File Path !                    ")
          msg2.setIcon(QMessageBox.Warning)
          y=msg2.exec_()

        
    def pushButton_handler2(self):
        
        try :
            #if os.path.basename(self.path).endswith('.elf'):
            self.progressBar.setValue(0)
            root = ET.Element("data")
  
            doc1 = ET.SubElement(root, "FileName").text= os.path.basename(self.path)
            doc2 = ET.SubElement(root, "CarsModel").text=  self.comboBox_2.currentText()
            doc3 = ET.SubElement(root, "CarsID").text=  self.comboBox_3.currentText()
            doc4 = ET.SubElement(root, "CarsTarget").text=  self.comboBox_4.currentText()            
            doc5 = ET.SubElement(root, "Status").text=  "Released"
           
            
            tree1 = ET.ElementTree(root)
            tree1.write("Request.xml")

            tree = ET.parse("Request.xml")
            root = tree.getroot()
      
            self.timer.start(5000)
            
    
            f=open(self.path,"r")
            f.close()
            #with open("Request.xml",'wb') as fileupdate :
            #  tree.write(fileupdate)  
            
            
            try:
              client = storage.Client.from_service_account_json(jsonFile)
              
              bucket = client.get_bucket('fotaproject_bucket')
              self.pathRequest=os.getcwd()
              print(self.pathRequest)
              blob1 = bucket.blob("Request.xml")
              blob1.upload_from_filename(self.pathRequest+"\Request.xml") 
              
              blob2 = bucket.blob(os.path.basename(self.path))
              blob2.upload_from_filename(self.path) 
              
              msgU = QMessageBox()
              msgU.setWindowTitle("Done!")
              msgU.setText("  Uploading done successfuly ! Waiting 1 minute on the Flashing status            ")
              msgU.setIcon(QMessageBox.Information)
              y=msgU.exec_()
   
              
            

              self.flag=0
              #self.checking()
              self.pushButton_2.setEnabled(False)
              self.pushButton.setEnabled(False)
              #self.comboBox.setEnabled(False)
            except Exception as ex1:
              msg3 = QMessageBox()
              msg3.setWindowTitle("Warning")
              msg3.setText("Failed Connecting to server for uploading the elf file !                    ")
              msg3.setIcon(QMessageBox.Warning)
              y=msg3.exec_()
          
        except Exception as ex:
          msg3 = QMessageBox()
          msg3.setWindowTitle("Warning")
          msg3.setText("Please Choose a correct File Path !              ")
          msg3.setIcon(QMessageBox.Warning)
          y=msg3.exec_()
    
    
   
       
        
        
    #def checking(self) :
    #  #download xml file
    #  try:        
    #    client = storage.Client.from_service_account_json(jsonFile)
    #    bucket = client.get_bucket('fotaproject_bucket')
    #    blob3 = bucket.blob("Request.xml")
    #    blob3.download_to_filename("Request.xml") 
    #
    #    tree = ET.parse("Request.xml")
    #    root = tree.getroot()
    #    indx=0
    #    tags =  [elem.tag for elem in root.iter()]
    #    attrs = [elem.text for elem in root.iter()]
    #    self.pushButton_3.setEnabled(False)
    #    #read xml parser
    #    for i in tags :
    #      if i == "Status" :
    #        print(attrs[indx])
    #        currentStatus=attrs[indx]
    #        break
    #      indx=indx+1
    #      
    #    
    #      
    #    #check if our action done .. break
    #    self.counter=self.counter+1
    #    self.t=threading.Timer(5, self.checking)        
    #    self.t.start()
    #    #if currentStatus =="Released" :
    #    #  #self.progressBar.repaint()
    #    #  #self.progressBar.reset()
    #    #  self.progressBar.setValue(33)
    #    #  self.label_5.setText(QCoreApplication.translate("Form", u"Released ", None))
    #    #
    #    #if currentStatus =="Downloaded" :
    #    #  #self.progressBar.repaint()
    #    #  #self.progressBar.reset()
    #    #  self.progressBar.update()
    #    #  self.progressBar.setValue(66)
    #    #  self.progressBar.update() 
    #    #  self.label_5.setText(QCoreApplication.translate("Form", u"Downloaded ", None))
    #    #  
    #    #if currentStatus =="Flashed" :
    #    #  #self.progressBar.repaint()
    #    #  self.progressBar.update()          
    #    #  self.progressBar.setValue(99)
    #    #  self.progressBar.update()          
    #    #  self.label_5.setText(QCoreApplication.translate("Form", u"Flashed ", None))
    #      
    #      
    #    if currentStatus =="Flashed" or currentStatus == "Error" or self.counter == 12:
    #   
    #      self.pushButton_3.setEnabled(True)  
    #      self.pushButton_2.setEnabled(True)
    #      self.pushButton.setEnabled(True)
    #      #self.comboBox.setEnabled(True)
    #      self.t.cancel()
    #      print("DONE !")
    #      #3ayzen nhandle popup window badal el slata de :D
    #      if self.counter != 12 : 
    #        print("hey1")
    #        if currentStatus == "Error" :
    #          print("hey2")
    #          root= tk.Tk()
    #          root.withdraw()
    #          tk.messagebox.showinfo("Status"," "+currentStatus+"                               ",icon = 'warning')
    #          #self.progressBar.setValue(0)
    #          #self.progressBar.setValue(100)
    #       #   self.progressBar.repaint()
    #          
    #          self.label_5.setText(QCoreApplication.translate("Form", u"Status ", None))
    #      
    #      
    #  except Exception as ex1:
    #    root2= tk.Tk()
    #    root2.withdraw()
    #    tk.messagebox.showinfo("Warning","Failed Connecting to server for Downloading the current status  !                    ",icon = 'warning')
    #    #msg4 = QMessageBox()
    #    #msg4.setWindowTitle("Warning")
    #    #msg4.setText("Failed Connecting to server for Downloading the current status  !                    ")
    #    #msg4.setIcon(QMessageBox.Warning)
    #    #y=msg4.exec_()

    def handleTimer(self):
        try:
          client = storage.Client.from_service_account_json(jsonFile)
          bucket = client.get_bucket('fotaproject_bucket')
          blob9 = bucket.blob("Request.xml")
          blob9.download_to_filename("Request.xml") 
          
          self.counter=self.counter+1
          
          tree = ET.parse("Request.xml")
          root = tree.getroot()
          indx=0
          tags =  [elem.tag for elem in root.iter()]
          attrs = [elem.text for elem in root.iter()]
          self.pushButton_3.setEnabled(False)
          #read xml parser
          for i in tags :
            if i == "Status" :
              print(attrs[indx])
              currentStatus=attrs[indx]
              break
            indx=indx+1
          
          if currentStatus =="Released" :
            #self.progressBar.repaint()
            #self.progressBar.reset()
            self.progressBar.setValue(33)
            self.label_5.setText(QCoreApplication.translate("Form", u"Released ", None))
          
          if currentStatus =="Downloaded" :
            #self.progressBar.repaint()
            #self.progressBar.reset()
            #self.progressBar.update()
            self.progressBar.setValue(66)
            #self.progressBar.update() 
            self.label_5.setText(QCoreApplication.translate("Form", u"Downloaded ", None))
            
          if currentStatus =="Flashed" :
            #self.progressBar.repaint()
            #self.progressBar.update()          
            self.progressBar.setValue(100)
            #self.progressBar.update()          
            self.label_5.setText(QCoreApplication.translate("Form", u"Flashed ", None))
            time.sleep(2)
            #print(self.counter)
          
          if currentStatus =="Flashed" or currentStatus == "Error" or self.counter == 12:
        
            self.counter=0
            self.pushButton_3.setEnabled(True)  
            self.pushButton_2.setEnabled(True)
            self.pushButton.setEnabled(True)
            #self.comboBox.setEnabled(True)
            #self.t.cancel()
            
            time.sleep(2)
            self.progressBar.setValue(0)
            self.label_5.setText(QCoreApplication.translate("Form", u"Status ", None))
            self.textEdit.clear()
            
            self.timer.stop()
            #print("DONE !")
            #3ayzen nhandle popup window badal el slata de :D
            if self.counter != 12 : 
              #print("hey1")
              if currentStatus == "Error" :
              #  print("hey2")
                root= tk.Tk()
                root.withdraw()
                tk.messagebox.showinfo("Status"," "+currentStatus+"                               ",icon = 'warning')

        except Exception as ex1:
          root2= tk.Tk()
          root2.withdraw()
          tk.messagebox.showinfo("Warning","Failed Connecting to server for Downloading the current status  !                    ",icon = 'warning')
          #msg4 = QMessageBox()
          #msg4.setWindowTitle("Warning")
          #msg4.setText("Failed Connecting to server for Downloading the current status  !                    ")
          #msg4.setIcon(QMessageBox.Warning)
          #y=msg4.exec_() 
        
        
        
    
    def pushButton_handler3(self):
      try:
        #print(self.comboBox_2.currentText())
        #print(self.comboBox_3.currentText())
        #print(self.comboBox_4.currentText())
        
        client = storage.Client.from_service_account_json(jsonFile)
        bucket = client.get_bucket('fotaproject_bucket')
        blob4 = bucket.blob("Request.xml")
        blob4.download_to_filename("Request.xml") 
  
        tree = ET.parse("Request.xml")
        root = tree.getroot()
        indx=0
        tags =  [elem.tag for elem in root.iter()]
        attrs = [elem.text for elem in root.iter()]
      
        #read xml parser
        for i in tags :
          if i == "Status" :
            print(attrs[indx])
            currentStatus=attrs[indx]
            break
          indx=indx+1
          
          
        msg1 = QMessageBox()
        msg1.setWindowTitle("Status")
        msg1.setText(""+currentStatus+"                               ")
        
        if currentStatus == "Error" :
          msg1.setIcon(QMessageBox.Warning)
          
          
        else :  
          msg1.setIcon(QMessageBox.Information)
        y=msg1.exec_()
      
      except Exception as ex1:
        msg5 = QMessageBox()
        msg5.setWindowTitle("Warning")
        msg5.setText("Failed Connecting to server for Downloading the Current status !                    ")
        msg5.setIcon(QMessageBox.Warning)
        y=msg5.exec_()
        
    def verify_Elf_File(self):
      file=open(self.path,"rb")
      try:
        elf_Handler =ELFFile(file)
        Header=elf_Handler.header   #elf file header
        Magic=Header.e_ident ['EI_MAG']
        elf_Class=elf_Handler.elfclass #elf file class   
      except Exception as ex1:
        return False
      if Magic[0] !=127 or  Magic[1] !=69 or  Magic[2] !=76 or  Magic[3] !=70 or  elf_Class !=32 :
        return False
      else: 
        return True
      
      
      
app = QApplication(sys.argv)
Widget = QWidget()
Form = Ui_Form()
Form.setupUi(Widget)
Widget.show()
sys.exit(app.exec_())

#Released //write
#Downloaded //read
#Error //read
#Flashed //read
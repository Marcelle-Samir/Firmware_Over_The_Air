# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'projectFOTA.ui'
##
## Created by: Qt User Interface Compiler version 5.14.0
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide2.QtCore import (QCoreApplication, QMetaObject, QObject, QPoint,
    QRect, QSize, QUrl, Qt)
from PySide2.QtGui import (QBrush, QColor, QConicalGradient, QFont,
    QFontDatabase, QIcon, QLinearGradient, QPalette, QPainter, QPixmap,
    QRadialGradient)
from PySide2.QtWidgets import *
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


jsonFile='fotaproject40-b1ae7c61a9cd.json'
class Ui_Form(object):
    def setupUi(self, Form):
        if Form.objectName():
            Form.setObjectName(u"Form")
        Form.resize(896, 563)
        self.pushButton = QPushButton(Form)
        self.pushButton.setObjectName(u"pushButton")
        self.pushButton.setGeometry(QRect(370, 10, 111, 51))
        self.pushButton.setStyleSheet(u"color:blue;\n"
"background-color: rgb(255, 255, 255);\n"
"border-style:outset;\n"
"")
        self.textEdit = QTextEdit(Form)
        self.textEdit.setObjectName(u"textEdit")
        self.textEdit.setGeometry(QRect(20, 10, 321, 51))
        self.textEdit.setStyleSheet(u"background-color: white;\n"
"font: 10pt \"MS Shell Dlg 2\";\n"
"")
        self.pushButton_2 = QPushButton(Form)
        self.pushButton_2.setObjectName(u"pushButton_2")
        self.pushButton_2.setGeometry(QRect(370, 80, 111, 51))
        self.pushButton_2.setStyleSheet(u"background-color:white;\n"
"color:blue;\n"
"border-style:outset;\n"
"")
        self.comboBox = QComboBox(Form)
        self.comboBox.addItem(u"STM32F103")
        self.comboBox.addItem(u"TivaC")
        self.comboBox.addItem(u"ATMEGA32")
        self.comboBox.setObjectName(u"comboBox")
        self.comboBox.setGeometry(QRect(110, 80, 171, 31))
        self.label_2 = QLabel(Form)
        self.label_2.setObjectName(u"label_2")
        self.label_2.setGeometry(QRect(20, 70, 101, 41))
        self.label_2.setStyleSheet(u"font: 11pt \"MS Shell Dlg 2\";")
        self.label_3 = QLabel(Form)
        self.label_3.setObjectName(u"label_3")
        self.label_3.setGeometry(QRect(520, -10, 481, 111))
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
        self.pushButton_3.setGeometry(QRect(110, 120, 171, 41))
        self.pushButton_3.setStyleSheet(u"background-color:white;\n"
"color:blue;\n"
"border-style:outset;")

        self.retranslateUi(Form)

        QMetaObject.connectSlotsByName(Form)
    # setupUi

    def retranslateUi(self, Form):
        Form.setWindowTitle(QCoreApplication.translate("Form", u"Form", None))
        self.pushButton.setText(QCoreApplication.translate("Form", u"BROWSE", None))
        self.pushButton.clicked.connect(self.pushButton_handler)
        self.textEdit.setHtml(QCoreApplication.translate("Form", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", None))
        self.pushButton_2.setText(QCoreApplication.translate("Form", u"UPLOAD", None))
        self.pushButton_2.clicked.connect(self.pushButton_handler2)
        self.comboBox.setItemText(0, QCoreApplication.translate("Form", u"STM32F103", None))
        self.comboBox.setItemText(1, QCoreApplication.translate("Form", u"TivaC", None))
        self.comboBox.setItemText(2, QCoreApplication.translate("Form", u"ATMEGA32", None))

        self.label_2.setText(QCoreApplication.translate("Form", u"Target :", None))
        self.label_3.setText(QCoreApplication.translate("Form", u"Firmware Over The Air", None))
        self.label_4.setText(QCoreApplication.translate("Form", u"FOTA", None))
        self.label.setText("")
        self.pushButton_3.setText(QCoreApplication.translate("Form", u"CHECK FLASHING STATUS", None))
        self.pushButton_3.clicked.connect(self.pushButton_handler3)
    # retranslateUi
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
          msg2 = QMessageBox()
          msg2.setWindowTitle("Warning")
          msg2.setText("Please Choose a File Path !                    ")
          msg2.setIcon(QMessageBox.Warning)
          y=msg2.exec_()

        
    def pushButton_handler2(self):
        try :
            #if os.path.basename(self.path).endswith('.elf'):
            root = ET.Element("data")
  
            doc1 = ET.SubElement(root, "FileName").text= os.path.basename(self.path)
            doc2 = ET.SubElement(root, "Target").text=  self.comboBox.currentText()
            doc3 = ET.SubElement(root, "Status").text=  "Released"
            
            
            tree1 = ET.ElementTree(root)
            tree1.write("Request.xml")

            tree = ET.parse("Request.xml")
            root = tree.getroot()
      
            
            
    
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
              
            
              self.counter=0
              self.flag=0
              self.checking()
            except Exception as ex1:
              msg3 = QMessageBox()
              msg3.setWindowTitle("Warning")
              msg3.setText("Failed Connecting to server !                    ")
              msg3.setIcon(QMessageBox.Warning)
              y=msg3.exec_()
          
        except Exception as ex:
          msg3 = QMessageBox()
          msg3.setWindowTitle("Warning")
          msg3.setText("Please Choose a correct File Path !              ")
          msg3.setIcon(QMessageBox.Warning)
          y=msg3.exec_()
    
    
   
       
        
        
    def checking(self) :
      #download xml file
      try:        
        client = storage.Client.from_service_account_json(jsonFile)
        bucket = client.get_bucket('fotaproject_bucket')
        blob3 = bucket.blob("Request.xml")
        blob3.download_to_filename("Request.xml") 
  
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
          
        
          
        #check if our action done .. break
        self.counter=self.counter+1
        self.t=threading.Timer(5, self.checking)        
        self.t.start()
        
        if currentStatus != "Released" or self.counter == 12:
          self.pushButton_3.setEnabled(True)  
          self.t.cancel()
          print("DONE !")
          #3ayzen nhandle popup window badal el slata de :D

          
      except Exception as ex1:
        msg4 = QMessageBox()
        msg4.setWindowTitle("Warning")
        msg4.setText("Failed Connecting to server !                    ")
        msg4.setIcon(QMessageBox.Warning)
        y=msg4.exec_()

    
    def pushButton_handler3(self):
      try:
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
        msg5.setText("Failed Connecting to server !                    ")
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
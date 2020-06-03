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
        print("Button pressed")
        self.open_dialog_box()
   
    def open_dialog_box(self):
        fileName = QFileDialog.getOpenFileName()
        self.path = fileName[0]
        self.textEdit.clear()
        self.textEdit.setText(self.path)
        print(os.path.basename(self.path))
        
        with open(self.path,"r") as f:
            print(f.readline())
        
    def pushButton_handler2(self):
        tree = ET.parse("Request.xml")
        root = tree.getroot()
       
        #f=open("Request.txt","w")
        #f.seek(0)
        #print("New Firmware "+self.comboBox.currentText()+" "+os.path.basename(self.path))
        #f.write("New Firmware "+self.comboBox.currentText()+" "+os.path.basename(self.path))
        #f.close()
        
        for elem in root.iter('Target'):
          elem.text = self.comboBox.currentText() 
          
          
        for elem in root.iter('Status'):
          elem.text = "Released"
        

        for elem in root.iter('FileName'):
          elem.text = os.path.basename(self.path)

          
        with open("Request.xml",'wb') as fileupdate :
          tree.write(fileupdate)  
        
        
        client = storage.Client.from_service_account_json('fotaproject40-b1ae7c61a9cd.json')
        
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
        
          
          
       
        
        
    def checking(self) :
      #download xml file
      client = storage.Client.from_service_account_json('fotaproject40-b1ae7c61a9cd.json')
      bucket = client.get_bucket('fotaproject_bucket')
      blob3 = bucket.blob("Request.xml")
      blob3.download_to_filename(self.pathRequest+"\Request.xml") 

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
      
      if currentStatus == "Flashed" or self.counter == 12:
        self.pushButton_3.setEnabled(True)  
        self.t.cancel()
        print("DONE !")
  

    
    def pushButton_handler3(self):
      client = storage.Client.from_service_account_json('fotaproject40-b1ae7c61a9cd.json')
      bucket = client.get_bucket('fotaproject_bucket')
      blob4 = bucket.blob("Request.xml")
      blob4.download_to_filename(self.pathRequest+"\Request.xml") 

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
        
      print("The Current Status is :"+currentStatus )



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
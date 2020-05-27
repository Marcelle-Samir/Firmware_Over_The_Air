# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'projectFOTAA.ui'
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
        self.textEdit.setStyleSheet(u"background-color: rgb(129, 194, 255);\n"
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
        self.label.setGeometry(QRect(30, 150, 841, 411))
        self.label.setPixmap(QPixmap(u"image/FOTAimg.jpg"))

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
   
        f=open("Request.txt","w")
        f.seek(0)
        print("New Firmware "+self.comboBox.currentText()+" "+os.path.basename(self.path))
        f.write("New Firmware "+self.comboBox.currentText()+" "+os.path.basename(self.path))
        f.close()
        
        
        client = storage.Client.from_service_account_json('FotaProject-d8e977316c43.json')
        
        bucket = client.get_bucket('fota_automotive')
        pathRequest=os.getcwd()
        print(pathRequest)
        blob1 = bucket.blob("Request.txt")
        blob1.upload_from_filename(pathRequest+"\Request.txt") 
        
        blob2 = bucket.blob(os.path.basename(self.path))
        blob2.upload_from_filename(self.path) 
        print("DONE !")




app = QApplication(sys.argv)
Widget = QWidget()
Form = Ui_Form()
Form.setupUi(Widget)
Widget.show()
sys.exit(app.exec_())
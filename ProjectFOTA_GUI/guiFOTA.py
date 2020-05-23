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
import chilkat

class Ui_Form(object):
    def setupUi(self, Form):
        if Form.objectName():
            Form.setObjectName(u"Form")
        Form.resize(850, 845)
        self.pushButton = QPushButton(Form)
        self.pushButton.setObjectName(u"pushButton")
        self.pushButton.setGeometry(QRect(510, 190, 111, 61))
        self.pushButton.setStyleSheet(u"background-color:white;\n"
"color:blue;\n"
"border-style:outset;\n"
"")
        self.textEdit = QTextEdit(Form)
        self.textEdit.setObjectName(u"textEdit")
        self.textEdit.setGeometry(QRect(150, 190, 321, 61))
        self.textEdit.setStyleSheet(u"background-color:pink;\n"
"color:blue;\n"
"border-style:outset;\n"
"")
        self.pushButton_2 = QPushButton(Form)
        self.pushButton_2.setObjectName(u"pushButton_2")
        self.pushButton_2.setGeometry(QRect(510, 270, 111, 61))
        self.pushButton_2.setStyleSheet(u"background-color:white;\n"
"color:blue;\n"
"border-style:outset;\n"
"")

        self.retranslateUi(Form)

        QMetaObject.connectSlotsByName(Form)
    # setupUi

    def retranslateUi(self, Form):
        Form.setWindowTitle(QCoreApplication.translate("Form", u"Form", None))
        self.pushButton.setText(QCoreApplication.translate("Form", u"BROWSE", None))
        self.pushButton.clicked.connect(self.pushButton_handler)
        self.pushButton_2.setText(QCoreApplication.translate("Form", u"UPLOAD", None))
        self.pushButton_2.clicked.connect(self.pushButton_handler2)
        
        
    def pushButton_handler(self):
        print("Button pressed")
        self.open_dialog_box()
   
    def open_dialog_box(self):
        fileName = QFileDialog.getOpenFileName()
        self.path = fileName[0]
        self.textEdit.clear()
        self.textEdit.setText(self.path)
        print(self.path)
        
        with open(self.path,"r") as f:
            print(f.readline())
        
    def pushButton_handler2(self):
        upload = chilkat.CkUpload()
    
        #  Specify the page (ASP, ASP.NET, Perl, Python, Ruby, CGI, etc)
        #  that will receive and process the HTTP Upload.
        upload.put_Hostname("www.mywebserver.com")
        upload.put_Path("/receiveUpload.aspx")
        
        #  Add one or more files to be uploaded.
        upload.AddFileReference("file1",self.path)
        print(self.path)
        #  Do the upload.  The method returns when the upload
        #  is completed.
        #  This component also includes asynchronous upload capability,
        #  which is demonstrated in another example.
        success = upload.BlockingUpload()
        if (success != True):
            print(upload.lastErrorText())
        else:
            print("Files uploaded!")
        
    # retranslateUi

app = QApplication(sys.argv)
Widget = QWidget()
Form = Ui_Form()
Form.setupUi(Widget)
Widget.show()
sys.exit(app.exec_())
/********************************************************************************
** Form generated from reading UI file 'EditorWidget.ui'
**
** Created: Thu Oct 11 15:34:28 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITORWIDGET_H
#define UI_EDITORWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditorWidget
{
  public:
    QHBoxLayout * horizontalLayout;
    QGroupBox * inspectorArea;
    QFormLayout * formLayout;
    QGridLayout * miscObjAttribsArea;
    QLineEdit * objectName;
    QLabel * objectNameLbl;
    QLineEdit * meshName;
    QLabel * meshLbl;
    QPushButton * browseMeshBtn;
    QLabel * textureLbl;
    QLineEdit * textureName;
    QPushButton * browseTextureBtn;
    QComboBox * textureFilter;
    QLabel * textureFilterLbl;
    QLabel * colorLbl;
    QGridLayout * colorEditor;
    QSpinBox * colorSelR;
    QSpinBox * colorSelG;
    QLabel * colorLblB;
    QSpinBox * colorSelB;
    QLabel * colorLblR;
    QLabel * colorLblG;
    QLabel * scaleLbl;
    QGridLayout * scaleEditor;
    QLabel * scaleLblX;
    QLabel * scaleLblZ;
    QLabel * scaleLblY;
    QDoubleSpinBox * scaleSelX;
    QDoubleSpinBox * scaleSelY;
    QDoubleSpinBox * scaleSelZ;
    QLabel * rotationLbl;
    QGridLayout * rotationEditor;
    QLabel * rotLblX;
    QLabel * rotLblY;
    QLabel * rotLblZ;
    QDoubleSpinBox * rotSelX;
    QDoubleSpinBox * rotSelY;
    QDoubleSpinBox * rotSelZ;
    QLabel * positionLbl;
    QGridLayout * positionEditor;
    QLabel * posLblX;
    QLabel * posLblY;
    QLabel * posLblZ;
    QDoubleSpinBox * posSelX;
    QDoubleSpinBox * posSelY;
    QDoubleSpinBox * posSelZ;
    QFrame * line0;
    QGridLayout * renderModeArea;
    QComboBox * rendererOpts;
    QLabel * renderModeLbl;
    QGridLayout * shininessArea;
    QLabel * shininessLbl;
    QSpinBox * shininessSel;
    QLabel * lightPosLbl;
    QGridLayout * lightPosEditor;
    QLabel * LposXLbl;
    QDoubleSpinBox * LposSelX;
    QLabel * LposYLbl;
    QDoubleSpinBox * LposSelY;
    QLabel * LposZLbl;
    QDoubleSpinBox * LposSelZ;
    QLabel * ambientLightLbl;
    QGridLayout * ambLightEditor;
    QLabel * ambRLbl;
    QSpinBox * ambRSel;
    QLabel * ambGLbl;
    QSpinBox * ambGSel;
    QLabel * ambBLbl;
    QSpinBox * ambBSel;
    QFrame * line1;
    QLabel * editorLbl;
    QGridLayout * btnArea;
    QPushButton * loadSceneBtn;
    QPushButton * saveSceneBtn;
    QPushButton * newObjBtn;
    QPushButton * removeObjBtn;
    QLabel * objectLbl;
    QLabel * rendererLbl;

    void setupUi(QWidget * EditorWidget)
    {
        if (EditorWidget->objectName().isEmpty())
            EditorWidget->setObjectName(QString::fromUtf8("EditorWidget"));
        EditorWidget->resize(1000, 950);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(EditorWidget->sizePolicy().hasHeightForWidth());
        EditorWidget->setSizePolicy(sizePolicy);
        EditorWidget->setLayoutDirection(Qt::LeftToRight);
        horizontalLayout = new QHBoxLayout(EditorWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        inspectorArea = new QGroupBox(EditorWidget);
        inspectorArea->setObjectName(QString::fromUtf8("inspectorArea"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(inspectorArea->sizePolicy().hasHeightForWidth());
        inspectorArea->setSizePolicy(sizePolicy1);
        formLayout = new QFormLayout(inspectorArea);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
        miscObjAttribsArea = new QGridLayout();
        miscObjAttribsArea->setSpacing(6);
        miscObjAttribsArea->setObjectName(QString::fromUtf8("miscObjAttribsArea"));
        objectName = new QLineEdit(inspectorArea);
        objectName->setObjectName(QString::fromUtf8("objectName"));

        miscObjAttribsArea->addWidget(objectName, 0, 2, 1, 1);

        objectNameLbl = new QLabel(inspectorArea);
        objectNameLbl->setObjectName(QString::fromUtf8("objectNameLbl"));

        miscObjAttribsArea->addWidget(objectNameLbl, 0, 0, 1, 1);

        meshName = new QLineEdit(inspectorArea);
        meshName->setObjectName(QString::fromUtf8("meshName"));
        meshName->setReadOnly(true);

        miscObjAttribsArea->addWidget(meshName, 1, 2, 1, 1);

        meshLbl = new QLabel(inspectorArea);
        meshLbl->setObjectName(QString::fromUtf8("meshLbl"));

        miscObjAttribsArea->addWidget(meshLbl, 1, 0, 1, 1);

        browseMeshBtn = new QPushButton(inspectorArea);
        browseMeshBtn->setObjectName(QString::fromUtf8("browseMeshBtn"));

        miscObjAttribsArea->addWidget(browseMeshBtn, 1, 3, 1, 1);

        textureLbl = new QLabel(inspectorArea);
        textureLbl->setObjectName(QString::fromUtf8("textureLbl"));

        miscObjAttribsArea->addWidget(textureLbl, 2, 0, 1, 1);

        textureName = new QLineEdit(inspectorArea);
        textureName->setObjectName(QString::fromUtf8("textureName"));
        textureName->setReadOnly(true);

        miscObjAttribsArea->addWidget(textureName, 2, 2, 1, 1);

        browseTextureBtn = new QPushButton(inspectorArea);
        browseTextureBtn->setObjectName(QString::fromUtf8("browseTextureBtn"));

        miscObjAttribsArea->addWidget(browseTextureBtn, 2, 3, 1, 1);

        textureFilter = new QComboBox(inspectorArea);
        textureFilter->setObjectName(QString::fromUtf8("textureFilter"));

        miscObjAttribsArea->addWidget(textureFilter, 3, 2, 1, 1);

        textureFilterLbl = new QLabel(inspectorArea);
        textureFilterLbl->setObjectName(QString::fromUtf8("textureFilterLbl"));

        miscObjAttribsArea->addWidget(textureFilterLbl, 3, 0, 1, 1);

        formLayout->setLayout(5, QFormLayout::SpanningRole, miscObjAttribsArea);

        colorLbl = new QLabel(inspectorArea);
        colorLbl->setObjectName(QString::fromUtf8("colorLbl"));

        formLayout->setWidget(14, QFormLayout::SpanningRole, colorLbl);

        colorEditor = new QGridLayout();
        colorEditor->setSpacing(6);
        colorEditor->setObjectName(QString::fromUtf8("colorEditor"));
        colorSelR = new QSpinBox(inspectorArea);
        colorSelR->setObjectName(QString::fromUtf8("colorSelR"));
        colorSelR->setMaximum(255);

        colorEditor->addWidget(colorSelR, 2, 2, 1, 1);

        colorSelG = new QSpinBox(inspectorArea);
        colorSelG->setObjectName(QString::fromUtf8("colorSelG"));
        colorSelG->setMaximum(255);

        colorEditor->addWidget(colorSelG, 2, 4, 1, 1);

        colorLblB = new QLabel(inspectorArea);
        colorLblB->setObjectName(QString::fromUtf8("colorLblB"));
        colorLblB->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);

        colorEditor->addWidget(colorLblB, 2, 5, 1, 1);

        colorSelB = new QSpinBox(inspectorArea);
        colorSelB->setObjectName(QString::fromUtf8("colorSelB"));
        colorSelB->setMaximum(255);

        colorEditor->addWidget(colorSelB, 2, 6, 1, 1);

        colorLblR = new QLabel(inspectorArea);
        colorLblR->setObjectName(QString::fromUtf8("colorLblR"));
        colorLblR->setLayoutDirection(Qt::LeftToRight);
        colorLblR->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);

        colorEditor->addWidget(colorLblR, 2, 0, 1, 1);

        colorLblG = new QLabel(inspectorArea);
        colorLblG->setObjectName(QString::fromUtf8("colorLblG"));
        colorLblG->setLayoutDirection(Qt::LeftToRight);
        colorLblG->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);

        colorEditor->addWidget(colorLblG, 2, 3, 1, 1);

        formLayout->setLayout(16, QFormLayout::SpanningRole, colorEditor);

        scaleLbl = new QLabel(inspectorArea);
        scaleLbl->setObjectName(QString::fromUtf8("scaleLbl"));

        formLayout->setWidget(17, QFormLayout::SpanningRole, scaleLbl);

        scaleEditor = new QGridLayout();
        scaleEditor->setSpacing(6);
        scaleEditor->setObjectName(QString::fromUtf8("scaleEditor"));
        scaleLblX = new QLabel(inspectorArea);
        scaleLblX->setObjectName(QString::fromUtf8("scaleLblX"));

        scaleEditor->addWidget(scaleLblX, 2, 0, 2, 1);

        scaleLblZ = new QLabel(inspectorArea);
        scaleLblZ->setObjectName(QString::fromUtf8("scaleLblZ"));

        scaleEditor->addWidget(scaleLblZ, 2, 5, 2, 1);

        scaleLblY = new QLabel(inspectorArea);
        scaleLblY->setObjectName(QString::fromUtf8("scaleLblY"));

        scaleEditor->addWidget(scaleLblY, 2, 2, 2, 1);

        scaleSelX = new QDoubleSpinBox(inspectorArea);
        scaleSelX->setObjectName(QString::fromUtf8("scaleSelX"));
        scaleSelX->setEnabled(true);
        scaleSelX->setWrapping(true);
        scaleSelX->setFrame(true);
        scaleSelX->setDecimals(2);
        scaleSelX->setMinimum(0);
        scaleSelX->setMaximum(1000);
        scaleSelX->setValue(0);

        scaleEditor->addWidget(scaleSelX, 2, 1, 2, 1);

        scaleSelY = new QDoubleSpinBox(inspectorArea);
        scaleSelY->setObjectName(QString::fromUtf8("scaleSelY"));
        scaleSelY->setWrapping(true);
        scaleSelY->setDecimals(2);
        scaleSelY->setMinimum(0);
        scaleSelY->setMaximum(1000);

        scaleEditor->addWidget(scaleSelY, 2, 3, 2, 1);

        scaleSelZ = new QDoubleSpinBox(inspectorArea);
        scaleSelZ->setObjectName(QString::fromUtf8("scaleSelZ"));
        scaleSelZ->setWrapping(true);
        scaleSelZ->setDecimals(2);
        scaleSelZ->setMinimum(0);
        scaleSelZ->setMaximum(1000);

        scaleEditor->addWidget(scaleSelZ, 2, 6, 2, 1);

        formLayout->setLayout(18, QFormLayout::SpanningRole, scaleEditor);

        rotationLbl = new QLabel(inspectorArea);
        rotationLbl->setObjectName(QString::fromUtf8("rotationLbl"));

        formLayout->setWidget(19, QFormLayout::SpanningRole, rotationLbl);

        rotationEditor = new QGridLayout();
        rotationEditor->setSpacing(6);
        rotationEditor->setObjectName(QString::fromUtf8("rotationEditor"));
        rotLblX = new QLabel(inspectorArea);
        rotLblX->setObjectName(QString::fromUtf8("rotLblX"));

        rotationEditor->addWidget(rotLblX, 0, 0, 2, 1);

        rotLblY = new QLabel(inspectorArea);
        rotLblY->setObjectName(QString::fromUtf8("rotLblY"));

        rotationEditor->addWidget(rotLblY, 0, 2, 2, 1);

        rotLblZ = new QLabel(inspectorArea);
        rotLblZ->setObjectName(QString::fromUtf8("rotLblZ"));

        rotationEditor->addWidget(rotLblZ, 0, 4, 2, 1);

        rotSelX = new QDoubleSpinBox(inspectorArea);
        rotSelX->setObjectName(QString::fromUtf8("rotSelX"));
        rotSelX->setWrapping(true);
        rotSelX->setMinimum(-360);
        rotSelX->setMaximum(360);

        rotationEditor->addWidget(rotSelX, 0, 1, 2, 1);

        rotSelY = new QDoubleSpinBox(inspectorArea);
        rotSelY->setObjectName(QString::fromUtf8("rotSelY"));
        rotSelY->setWrapping(true);
        rotSelY->setMinimum(-360);
        rotSelY->setMaximum(360);

        rotationEditor->addWidget(rotSelY, 0, 3, 2, 1);

        rotSelZ = new QDoubleSpinBox(inspectorArea);
        rotSelZ->setObjectName(QString::fromUtf8("rotSelZ"));
        rotSelZ->setWrapping(true);
        rotSelZ->setMinimum(-360);
        rotSelZ->setMaximum(360);

        rotationEditor->addWidget(rotSelZ, 0, 5, 2, 1);

        formLayout->setLayout(20, QFormLayout::SpanningRole, rotationEditor);

        positionLbl = new QLabel(inspectorArea);
        positionLbl->setObjectName(QString::fromUtf8("positionLbl"));

        formLayout->setWidget(23, QFormLayout::SpanningRole, positionLbl);

        positionEditor = new QGridLayout();
        positionEditor->setSpacing(6);
        positionEditor->setObjectName(QString::fromUtf8("positionEditor"));
        posLblX = new QLabel(inspectorArea);
        posLblX->setObjectName(QString::fromUtf8("posLblX"));

        positionEditor->addWidget(posLblX, 0, 0, 1, 1);

        posLblY = new QLabel(inspectorArea);
        posLblY->setObjectName(QString::fromUtf8("posLblY"));

        positionEditor->addWidget(posLblY, 0, 2, 1, 1);

        posLblZ = new QLabel(inspectorArea);
        posLblZ->setObjectName(QString::fromUtf8("posLblZ"));

        positionEditor->addWidget(posLblZ, 0, 4, 1, 1);

        posSelX = new QDoubleSpinBox(inspectorArea);
        posSelX->setObjectName(QString::fromUtf8("posSelX"));
        posSelX->setWrapping(true);
        posSelX->setDecimals(1);
        posSelX->setMinimum(-10000);
        posSelX->setMaximum(10000);

        positionEditor->addWidget(posSelX, 0, 1, 1, 1);

        posSelY = new QDoubleSpinBox(inspectorArea);
        posSelY->setObjectName(QString::fromUtf8("posSelY"));
        posSelY->setWrapping(true);
        posSelY->setDecimals(1);
        posSelY->setMinimum(-10000);
        posSelY->setMaximum(10000);

        positionEditor->addWidget(posSelY, 0, 3, 1, 1);

        posSelZ = new QDoubleSpinBox(inspectorArea);
        posSelZ->setObjectName(QString::fromUtf8("posSelZ"));
        posSelZ->setWrapping(true);
        posSelZ->setDecimals(1);
        posSelZ->setMinimum(-10000);
        posSelZ->setMaximum(10000);

        positionEditor->addWidget(posSelZ, 0, 5, 1, 1);

        formLayout->setLayout(24, QFormLayout::SpanningRole, positionEditor);

        line0 = new QFrame(inspectorArea);
        line0->setObjectName(QString::fromUtf8("line0"));
        line0->setFrameShape(QFrame::HLine);
        line0->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(25, QFormLayout::SpanningRole, line0);

        renderModeArea = new QGridLayout();
        renderModeArea->setSpacing(6);
        renderModeArea->setObjectName(QString::fromUtf8("renderModeArea"));
        rendererOpts = new QComboBox(inspectorArea);
        rendererOpts->setObjectName(QString::fromUtf8("rendererOpts"));

        renderModeArea->addWidget(rendererOpts, 0, 1, 1, 1);

        renderModeLbl = new QLabel(inspectorArea);
        renderModeLbl->setObjectName(QString::fromUtf8("renderModeLbl"));

        renderModeArea->addWidget(renderModeLbl, 0, 0, 1, 1);

        formLayout->setLayout(29, QFormLayout::LabelRole, renderModeArea);

        shininessArea = new QGridLayout();
        shininessArea->setSpacing(6);
        shininessArea->setObjectName(QString::fromUtf8("shininessArea"));
        shininessLbl = new QLabel(inspectorArea);
        shininessLbl->setObjectName(QString::fromUtf8("shininessLbl"));

        shininessArea->addWidget(shininessLbl, 0, 0, 1, 1);

        shininessSel = new QSpinBox(inspectorArea);
        shininessSel->setObjectName(QString::fromUtf8("shininessSel"));
        shininessSel->setWrapping(true);

        shininessArea->addWidget(shininessSel, 0, 1, 1, 1);

        formLayout->setLayout(29, QFormLayout::FieldRole, shininessArea);

        lightPosLbl = new QLabel(inspectorArea);
        lightPosLbl->setObjectName(QString::fromUtf8("lightPosLbl"));

        formLayout->setWidget(30, QFormLayout::SpanningRole, lightPosLbl);

        lightPosEditor = new QGridLayout();
        lightPosEditor->setSpacing(6);
        lightPosEditor->setObjectName(QString::fromUtf8("lightPosEditor"));
        LposXLbl = new QLabel(inspectorArea);
        LposXLbl->setObjectName(QString::fromUtf8("LposXLbl"));

        lightPosEditor->addWidget(LposXLbl, 0, 0, 1, 1);

        LposSelX = new QDoubleSpinBox(inspectorArea);
        LposSelX->setObjectName(QString::fromUtf8("LposSelX"));
        LposSelX->setWrapping(true);
        LposSelX->setDecimals(1);
        LposSelX->setMinimum(-10000);
        LposSelX->setMaximum(10000);
        LposSelX->setValue(0);

        lightPosEditor->addWidget(LposSelX, 0, 1, 1, 1);

        LposYLbl = new QLabel(inspectorArea);
        LposYLbl->setObjectName(QString::fromUtf8("LposYLbl"));

        lightPosEditor->addWidget(LposYLbl, 0, 2, 1, 1);

        LposSelY = new QDoubleSpinBox(inspectorArea);
        LposSelY->setObjectName(QString::fromUtf8("LposSelY"));
        LposSelY->setWrapping(true);
        LposSelY->setDecimals(1);
        LposSelY->setMinimum(-10000);
        LposSelY->setMaximum(10000);

        lightPosEditor->addWidget(LposSelY, 0, 3, 1, 1);

        LposZLbl = new QLabel(inspectorArea);
        LposZLbl->setObjectName(QString::fromUtf8("LposZLbl"));

        lightPosEditor->addWidget(LposZLbl, 0, 4, 1, 1);

        LposSelZ = new QDoubleSpinBox(inspectorArea);
        LposSelZ->setObjectName(QString::fromUtf8("LposSelZ"));
        LposSelZ->setWrapping(true);
        LposSelZ->setDecimals(1);
        LposSelZ->setMinimum(-10000);
        LposSelZ->setMaximum(10000);

        lightPosEditor->addWidget(LposSelZ, 0, 5, 1, 1);

        formLayout->setLayout(31, QFormLayout::SpanningRole, lightPosEditor);

        ambientLightLbl = new QLabel(inspectorArea);
        ambientLightLbl->setObjectName(QString::fromUtf8("ambientLightLbl"));

        formLayout->setWidget(32, QFormLayout::SpanningRole, ambientLightLbl);

        ambLightEditor = new QGridLayout();
        ambLightEditor->setSpacing(6);
        ambLightEditor->setObjectName(QString::fromUtf8("ambLightEditor"));
        ambRLbl = new QLabel(inspectorArea);
        ambRLbl->setObjectName(QString::fromUtf8("ambRLbl"));

        ambLightEditor->addWidget(ambRLbl, 0, 0, 1, 1);

        ambRSel = new QSpinBox(inspectorArea);
        ambRSel->setObjectName(QString::fromUtf8("ambRSel"));
        ambRSel->setWrapping(true);
        ambRSel->setMaximum(255);

        ambLightEditor->addWidget(ambRSel, 0, 1, 1, 1);

        ambGLbl = new QLabel(inspectorArea);
        ambGLbl->setObjectName(QString::fromUtf8("ambGLbl"));

        ambLightEditor->addWidget(ambGLbl, 0, 2, 1, 1);

        ambGSel = new QSpinBox(inspectorArea);
        ambGSel->setObjectName(QString::fromUtf8("ambGSel"));
        ambGSel->setWrapping(true);
        ambGSel->setMaximum(255);

        ambLightEditor->addWidget(ambGSel, 0, 3, 1, 1);

        ambBLbl = new QLabel(inspectorArea);
        ambBLbl->setObjectName(QString::fromUtf8("ambBLbl"));

        ambLightEditor->addWidget(ambBLbl, 0, 4, 1, 1);

        ambBSel = new QSpinBox(inspectorArea);
        ambBSel->setObjectName(QString::fromUtf8("ambBSel"));
        ambBSel->setWrapping(true);
        ambBSel->setMaximum(255);

        ambLightEditor->addWidget(ambBSel, 0, 5, 1, 1);

        formLayout->setLayout(33, QFormLayout::SpanningRole, ambLightEditor);

        line1 = new QFrame(inspectorArea);
        line1->setObjectName(QString::fromUtf8("line1"));
        line1->setFrameShape(QFrame::HLine);
        line1->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(34, QFormLayout::SpanningRole, line1);

        editorLbl = new QLabel(inspectorArea);
        editorLbl->setObjectName(QString::fromUtf8("editorLbl"));
        editorLbl->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(35, QFormLayout::SpanningRole, editorLbl);

        btnArea = new QGridLayout();
        btnArea->setSpacing(6);
        btnArea->setObjectName(QString::fromUtf8("btnArea"));
        loadSceneBtn = new QPushButton(inspectorArea);
        loadSceneBtn->setObjectName(QString::fromUtf8("loadSceneBtn"));

        btnArea->addWidget(loadSceneBtn, 3, 1, 1, 1);

        saveSceneBtn = new QPushButton(inspectorArea);
        saveSceneBtn->setObjectName(QString::fromUtf8("saveSceneBtn"));

        btnArea->addWidget(saveSceneBtn, 3, 0, 1, 1);

        newObjBtn = new QPushButton(inspectorArea);
        newObjBtn->setObjectName(QString::fromUtf8("newObjBtn"));

        btnArea->addWidget(newObjBtn, 1, 0, 1, 1);

        removeObjBtn = new QPushButton(inspectorArea);
        removeObjBtn->setObjectName(QString::fromUtf8("removeObjBtn"));

        btnArea->addWidget(removeObjBtn, 1, 1, 1, 1);

        formLayout->setLayout(36, QFormLayout::SpanningRole, btnArea);

        objectLbl = new QLabel(inspectorArea);
        objectLbl->setObjectName(QString::fromUtf8("objectLbl"));
        objectLbl->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(3, QFormLayout::SpanningRole, objectLbl);

        rendererLbl = new QLabel(inspectorArea);
        rendererLbl->setObjectName(QString::fromUtf8("rendererLbl"));
        rendererLbl->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(27, QFormLayout::SpanningRole, rendererLbl);

        horizontalLayout->addWidget(inspectorArea);

        retranslateUi(EditorWidget);

        QMetaObject::connectSlotsByName(EditorWidget);
    } // setupUi

    void retranslateUi(QWidget * EditorWidget)
    {
        EditorWidget->setWindowTitle(QApplication::translate("EditorWidget", "Lampert's 3D Scene Editor", 0, QApplication::UnicodeUTF8));
        inspectorArea->setTitle(QApplication::translate("EditorWidget", "Inspector", 0, QApplication::UnicodeUTF8));
        objectNameLbl->setText(QApplication::translate("EditorWidget", "Object Name:", 0, QApplication::UnicodeUTF8));
        meshLbl->setText(QApplication::translate("EditorWidget", "Mesh:", 0, QApplication::UnicodeUTF8));
        browseMeshBtn->setText(QApplication::translate("EditorWidget", "Browse", 0, QApplication::UnicodeUTF8));
        textureLbl->setText(QApplication::translate("EditorWidget", "Texture:", 0, QApplication::UnicodeUTF8));
        browseTextureBtn->setText(QApplication::translate("EditorWidget", "Browse", 0, QApplication::UnicodeUTF8));
        textureFilterLbl->setText(QApplication::translate("EditorWidget", "Texture Quality:", 0, QApplication::UnicodeUTF8));
        colorLbl->setText(QApplication::translate("EditorWidget", "Color:", 0, QApplication::UnicodeUTF8));
        colorLblB->setText(QApplication::translate("EditorWidget", "B:", 0, QApplication::UnicodeUTF8));
        colorLblR->setText(QApplication::translate("EditorWidget", "R:", 0, QApplication::UnicodeUTF8));
        colorLblG->setText(QApplication::translate("EditorWidget", "G:", 0, QApplication::UnicodeUTF8));
        scaleLbl->setText(QApplication::translate("EditorWidget", "Scale:", 0, QApplication::UnicodeUTF8));
        scaleLblX->setText(QApplication::translate("EditorWidget", "X:", 0, QApplication::UnicodeUTF8));
        scaleLblZ->setText(QApplication::translate("EditorWidget", "Z:", 0, QApplication::UnicodeUTF8));
        scaleLblY->setText(QApplication::translate("EditorWidget", "Y:", 0, QApplication::UnicodeUTF8));
        rotationLbl->setText(QApplication::translate("EditorWidget", "Rotation:", 0, QApplication::UnicodeUTF8));
        rotLblX->setText(QApplication::translate("EditorWidget", "X:", 0, QApplication::UnicodeUTF8));
        rotLblY->setText(QApplication::translate("EditorWidget", "Y:", 0, QApplication::UnicodeUTF8));
        rotLblZ->setText(QApplication::translate("EditorWidget", "Z:", 0, QApplication::UnicodeUTF8));
        positionLbl->setText(QApplication::translate("EditorWidget", "World Position:", 0, QApplication::UnicodeUTF8));
        posLblX->setText(QApplication::translate("EditorWidget", "X:", 0, QApplication::UnicodeUTF8));
        posLblY->setText(QApplication::translate("EditorWidget", "Y:", 0, QApplication::UnicodeUTF8));
        posLblZ->setText(QApplication::translate("EditorWidget", "Z:", 0, QApplication::UnicodeUTF8));
        renderModeLbl->setText(QApplication::translate("EditorWidget", "Render Mode:", 0, QApplication::UnicodeUTF8));
        shininessLbl->setText(QApplication::translate("EditorWidget", "Shininess:", 0, QApplication::UnicodeUTF8));
        lightPosLbl->setText(QApplication::translate("EditorWidget", "Light Position:", 0, QApplication::UnicodeUTF8));
        LposXLbl->setText(QApplication::translate("EditorWidget", "X:", 0, QApplication::UnicodeUTF8));
        LposYLbl->setText(QApplication::translate("EditorWidget", "Y:", 0, QApplication::UnicodeUTF8));
        LposZLbl->setText(QApplication::translate("EditorWidget", "Z:", 0, QApplication::UnicodeUTF8));
        ambientLightLbl->setText(QApplication::translate("EditorWidget", "Ambient Light:", 0, QApplication::UnicodeUTF8));
        ambRLbl->setText(QApplication::translate("EditorWidget", "R:", 0, QApplication::UnicodeUTF8));
        ambGLbl->setText(QApplication::translate("EditorWidget", "G:", 0, QApplication::UnicodeUTF8));
        ambBLbl->setText(QApplication::translate("EditorWidget", "B:", 0, QApplication::UnicodeUTF8));
        editorLbl->setText(QApplication::translate("EditorWidget", "Editor", 0, QApplication::UnicodeUTF8));
        loadSceneBtn->setText(QApplication::translate("EditorWidget", "Load Scene", 0, QApplication::UnicodeUTF8));
        saveSceneBtn->setText(QApplication::translate("EditorWidget", "Save Scene", 0, QApplication::UnicodeUTF8));
        newObjBtn->setText(QApplication::translate("EditorWidget", "New Object", 0, QApplication::UnicodeUTF8));
        removeObjBtn->setText(QApplication::translate("EditorWidget", "Remove Object", 0, QApplication::UnicodeUTF8));
        objectLbl->setText(QApplication::translate("EditorWidget", "Object", 0, QApplication::UnicodeUTF8));
        rendererLbl->setText(QApplication::translate("EditorWidget", "Renderer", 0, QApplication::UnicodeUTF8));
    } // retranslateUi
};

namespace Ui
{
class EditorWidget : public Ui_EditorWidget
{
};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITORWIDGET_H

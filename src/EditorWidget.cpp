
// ===============================================================================================================
// -*- C++ -*-
//
// EditorWidget.cpp - L3D Editor window.
//
// Copyright (c) 2012 Guilherme R. Lampert
// guilherme.ronaldo.lampert@gmail.com
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// above is included in the resulting source code.
//
// ===============================================================================================================

#include "EditorWidget.hpp"
#include "GLWidget.hpp"
#include "Renderer.hpp"
#include "ui_EditorWidget.h"

l3d::EditorWidget::EditorWidget(QWidget * parent)
    : QWidget(parent)
    , ui(new Ui::EditorWidget)
{
    editorWindow = this;

    ui->setupUi(this);

    qglContext = new GLWidget;
    ui->horizontalLayout->addWidget(qglContext);

    qglContext->setFocus();
}

l3d::EditorWidget::~EditorWidget()
{
    editorWindow = 0;

    delete qglContext;
    qglContext = 0;

    delete ui;
}

namespace l3d
{
EditorWidget * editorWindow = 0;
}

int l3d::EditorWidget::getInspectorXOffset() const
{
    return ui->inspectorArea->width();
}

void l3d::EditorWidget::initUI()
{
    ui->rendererOpts->addItem("Wireframe"); // 0 - RM_WIREFRAME
    ui->rendererOpts->addItem("Solid");     // 1 - RM_TEXTURE_SHADED
    ui->rendererOpts->setCurrentIndex(1);

    // Set current light properties in the UI
    ui->shininessSel->setValue(qglContext->renderer->shininess);
    ui->LposSelX->setValue(qglContext->renderer->lightPosition.x());
    ui->LposSelY->setValue(qglContext->renderer->lightPosition.y());
    ui->LposSelZ->setValue(qglContext->renderer->lightPosition.z());
    ui->ambRSel->setValue(static_cast<int>(qglContext->renderer->ambientLight.x() * 255.0f));
    ui->ambGSel->setValue(static_cast<int>(qglContext->renderer->ambientLight.y() * 255.0f));
    ui->ambBSel->setValue(static_cast<int>(qglContext->renderer->ambientLight.z() * 255.0f));

    resetUI();
}

void l3d::EditorWidget::resetUI()
{
    if (qglContext->selectedObj)
    {
        enableUI(true);

        ui->meshName->setText(qglContext->selectedObj->GetMesh().c_str());
        ui->textureName->setText(qglContext->selectedObj->GetTexture().c_str());
        ui->objectName->setText(qglContext->selectedObj->objectName.c_str());

        // Texture qualities/filters
        ui->textureFilter->clear();
        ui->textureFilter->addItem("Low");    // 0 - TF_LOW
        ui->textureFilter->addItem("Medium"); // 1 - TF_MEDIUM
        ui->textureFilter->addItem("High");   // 2 - TF_HIGH
        ui->textureFilter->setCurrentIndex(qglContext->selectedObj->materials[0].textureFilter);

        // Fill the Color spin boxes:
        ui->colorSelR->setValue(qglContext->selectedObj->materials[0].color.red());
        ui->colorSelG->setValue(qglContext->selectedObj->materials[0].color.green());
        ui->colorSelB->setValue(qglContext->selectedObj->materials[0].color.blue());

        // Fill the Rotation spin boxes:
        ui->rotSelX->setValue(qglContext->selectedObj->xform.rotation.x());
        ui->rotSelX->setValue(qglContext->selectedObj->xform.rotation.y());
        ui->rotSelX->setValue(qglContext->selectedObj->xform.rotation.z());

        // Fill the Scale spin boxes:
        ui->scaleSelX->setValue(qglContext->selectedObj->xform.scale.x());
        ui->scaleSelY->setValue(qglContext->selectedObj->xform.scale.y());
        ui->scaleSelZ->setValue(qglContext->selectedObj->xform.scale.z());

        // Fill the Position spin boxes:
        ui->posSelX->setValue(qglContext->selectedObj->xform.translation.x());
        ui->posSelY->setValue(qglContext->selectedObj->xform.translation.y());
        ui->posSelZ->setValue(qglContext->selectedObj->xform.translation.z());
    }
    else
    {
        // No object currently selected, will disable all the controls
        enableUI(false);
    }
}

void l3d::EditorWidget::enableUI(bool enabled)
{
    ui->browseMeshBtn->setEnabled(enabled);
    ui->browseTextureBtn->setEnabled(enabled);
    ui->meshName->setEnabled(enabled);
    ui->textureName->setEnabled(enabled);
    ui->objectName->setEnabled(enabled);
    ui->textureFilter->setEnabled(enabled);
    ui->colorSelR->setEnabled(enabled);
    ui->colorSelG->setEnabled(enabled);
    ui->colorSelB->setEnabled(enabled);
    ui->rotSelX->setEnabled(enabled);
    ui->rotSelY->setEnabled(enabled);
    ui->rotSelZ->setEnabled(enabled);
    ui->scaleSelX->setEnabled(enabled);
    ui->scaleSelY->setEnabled(enabled);
    ui->scaleSelZ->setEnabled(enabled);
    ui->posSelX->setEnabled(enabled);
    ui->posSelY->setEnabled(enabled);
    ui->posSelZ->setEnabled(enabled);

    if (!enabled)
    {
        // Set all values to default ones:
        ui->meshName->setText("");
        ui->textureName->setText("");
        ui->objectName->setText("");
        ui->textureFilter->clear();
        ui->colorSelR->setValue(0);
        ui->colorSelG->setValue(0);
        ui->colorSelB->setValue(0);
        ui->rotSelX->setValue(0);
        ui->rotSelY->setValue(0);
        ui->rotSelZ->setValue(0);
        ui->scaleSelX->setValue(0);
        ui->scaleSelY->setValue(0);
        ui->scaleSelZ->setValue(0);
        ui->posSelX->setValue(0);
        ui->posSelY->setValue(0);
        ui->posSelZ->setValue(0);
    }
}

#define NULL_OBJ_GUARD            \
    if (!qglContext->selectedObj) \
    {                             \
        return;                   \
    }

void l3d::EditorWidget::on_objectName_editingFinished()
{
    NULL_OBJ_GUARD
    qglContext->selectedObj->objectName = ui->objectName->text().toStdString();
}

void l3d::EditorWidget::on_posSelX_editingFinished()
{
    on_posSelX_valueChanged(ui->posSelX->value());
}

void l3d::EditorWidget::on_posSelY_editingFinished()
{
    on_posSelY_valueChanged(ui->posSelY->value());
}

void l3d::EditorWidget::on_posSelZ_editingFinished()
{
    on_posSelZ_valueChanged(ui->posSelZ->value());
}

void l3d::EditorWidget::on_rotSelX_editingFinished()
{
    on_rotSelX_valueChanged(ui->rotSelX->value());
}

void l3d::EditorWidget::on_rotSelY_editingFinished()
{
    on_rotSelY_valueChanged(ui->rotSelY->value());
}

void l3d::EditorWidget::on_rotSelZ_editingFinished()
{
    on_rotSelZ_valueChanged(ui->rotSelZ->value());
}

void l3d::EditorWidget::on_scaleSelX_editingFinished()
{
    on_scaleSelX_valueChanged(ui->scaleSelX->value());
}

void l3d::EditorWidget::on_scaleSelY_editingFinished()
{
    on_scaleSelY_valueChanged(ui->scaleSelY->value());
}

void l3d::EditorWidget::on_scaleSelZ_editingFinished()
{
    on_scaleSelZ_valueChanged(ui->scaleSelZ->value());
}

void l3d::EditorWidget::on_colorSelR_editingFinished()
{
    on_colorSelR_valueChanged(ui->colorSelR->value());
}

void l3d::EditorWidget::on_colorSelG_editingFinished()
{
    on_colorSelG_valueChanged(ui->colorSelG->value());
}

void l3d::EditorWidget::on_colorSelB_editingFinished()
{
    on_colorSelB_valueChanged(ui->colorSelB->value());
}

void l3d::EditorWidget::on_browseTextureBtn_clicked()
{
    NULL_OBJ_GUARD

    QString fileName = QFileDialog::getOpenFileName(this, "Load Texture",
                                                    QString(), "Images (*.png *.bmp *.jpg *.jpeg *.pcx *.tif *.tga)");

    if (!fileName.isEmpty())
    {
        if (qglContext->selectedObj->SetTexture(fileName.toStdString()))
        {
            ui->textureName->setText(fileName);
        }
    }
}

void l3d::EditorWidget::on_browseMeshBtn_clicked()
{
    NULL_OBJ_GUARD

    QString fileName = QFileDialog::getOpenFileName(this, "Load Mesh", QString(), "Mesh Files (*.*)");

    if (!fileName.isEmpty())
    {
        // This will also set the texture to the one associated to this new mesh.
        if (qglContext->selectedObj->SetMesh(fileName.toStdString()))
        {
            ui->meshName->setText(fileName);
            ui->textureName->setText(qglContext->selectedObj->GetTexture().c_str());
            ui->textureFilter->setCurrentIndex(qglContext->selectedObj->materials[0].textureFilter);
        }
    }
}

void l3d::EditorWidget::on_textureFilter_activated(int index)
{
    NULL_OBJ_GUARD
    qglContext->selectedObj->materials[0].textureFilter = static_cast<TextureFilter>(index);
}

void l3d::EditorWidget::on_scaleSelX_valueChanged(double arg1)
{
    NULL_OBJ_GUARD
    qglContext->selectedObj->xform.scale.setX(static_cast<float>(arg1));
}

void l3d::EditorWidget::on_scaleSelY_valueChanged(double arg1)
{
    NULL_OBJ_GUARD
    qglContext->selectedObj->xform.scale.setY(static_cast<float>(arg1));
}

void l3d::EditorWidget::on_scaleSelZ_valueChanged(double arg1)
{
    NULL_OBJ_GUARD
    qglContext->selectedObj->xform.scale.setZ(static_cast<float>(arg1));
}

void l3d::EditorWidget::on_rotSelX_valueChanged(double arg1)
{
    NULL_OBJ_GUARD
    qglContext->selectedObj->xform.rotation.setX(arg1);
}

void l3d::EditorWidget::on_rotSelY_valueChanged(double arg1)
{
    NULL_OBJ_GUARD
    qglContext->selectedObj->xform.rotation.setY(arg1);
}

void l3d::EditorWidget::on_rotSelZ_valueChanged(double arg1)
{
    NULL_OBJ_GUARD
    qglContext->selectedObj->xform.rotation.setZ(arg1);
}

void l3d::EditorWidget::on_posSelX_valueChanged(double arg1)
{
    NULL_OBJ_GUARD
    qglContext->selectedObj->xform.translation.setX(static_cast<float>(arg1));
}

void l3d::EditorWidget::on_posSelY_valueChanged(double arg1)
{
    NULL_OBJ_GUARD
    qglContext->selectedObj->xform.translation.setY(static_cast<float>(arg1));
}

void l3d::EditorWidget::on_posSelZ_valueChanged(double arg1)
{
    NULL_OBJ_GUARD
    qglContext->selectedObj->xform.translation.setZ(static_cast<float>(arg1));
}

void l3d::EditorWidget::on_colorSelR_valueChanged(int arg1)
{
    NULL_OBJ_GUARD
    qglContext->selectedObj->materials[0].color.setRed(arg1);
}

void l3d::EditorWidget::on_colorSelG_valueChanged(int arg1)
{
    NULL_OBJ_GUARD
    qglContext->selectedObj->materials[0].color.setGreen(arg1);
}

void l3d::EditorWidget::on_colorSelB_valueChanged(int arg1)
{
    NULL_OBJ_GUARD
    qglContext->selectedObj->materials[0].color.setBlue(arg1);
}

void l3d::EditorWidget::on_rendererOpts_activated(int index)
{
    qglContext->renderer->SetRenderMode(static_cast<RenderMode>(index));
}

void l3d::EditorWidget::on_removeObjBtn_clicked()
{
    NULL_OBJ_GUARD
    qglContext->scene->RemoveObject(qglContext->selectedObj);
    qglContext->selectedObj = 0;
    resetUI();
}

void l3d::EditorWidget::on_newObjBtn_clicked()
{
    qglContext->selectedObj = qglContext->scene->NewObject();
    resetUI();
}

void l3d::EditorWidget::on_loadSceneBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Load Scene", QString(), "L3D Scene (*.l3d)");

    if (!fileName.isEmpty())
    {
        qglContext->selectedObj = 0;
        resetUI();

        if (!qglContext->scene->Load(fileName.toStdString(), &qglContext->camera))
        {
            QMessageBox::critical(0, "Failure", "Failed to load scene file...");
        }
    }
}

void l3d::EditorWidget::on_saveSceneBtn_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Scene", QString(), "L3D Scene (*.l3d)");

    if (!fileName.isEmpty())
    {
        if (qglContext->scene->Save(fileName.toStdString(), &qglContext->camera))
        {
            QMessageBox::information(0, "Success", "Scene saved successfully!");
        }
        else
        {
            QMessageBox::critical(0, "Failure", "Failed to save the scene!");
        }
    }
}

void l3d::EditorWidget::on_shininessSel_valueChanged(int arg1)
{
    qglContext->renderer->shininess = static_cast<float>(arg1);
}

void l3d::EditorWidget::on_LposSelX_valueChanged(double arg1)
{
    qglContext->renderer->lightPosition.setX(arg1);
}

void l3d::EditorWidget::on_LposSelY_valueChanged(double arg1)
{
    qglContext->renderer->lightPosition.setY(arg1);
}

void l3d::EditorWidget::on_LposSelZ_valueChanged(double arg1)
{
    qglContext->renderer->lightPosition.setZ(arg1);
}

void l3d::EditorWidget::on_ambRSel_valueChanged(int arg1)
{
    qglContext->renderer->ambientLight.setX(static_cast<float>(arg1 * (1.0f / 255.0f)));
}

void l3d::EditorWidget::on_ambGSel_valueChanged(int arg1)
{
    qglContext->renderer->ambientLight.setY(static_cast<float>(arg1 * (1.0f / 255.0f)));
}

void l3d::EditorWidget::on_ambBSel_valueChanged(int arg1)
{
    qglContext->renderer->ambientLight.setZ(static_cast<float>(arg1 * (1.0f / 255.0f)));
}

#undef NULL_OBJ_GUARD

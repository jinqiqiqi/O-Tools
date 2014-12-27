#include "otools.h"
#include "ui_otools.h"
#include <stdlib.h>
#include <QApplication>
#include <QComboBox>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QProgressDialog>

QString device("unknow");

OTools::OTools(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OTools)
{
    ui->setupUi(this);
}

OTools::~OTools()
{
    delete ui;
}

// ToolBar

void OTools::on_actionDisclaimer_triggered()
{
    QMessageBox::critical(this,tr("Disclaimer"),"This program has enough knowledge to brick your device, destroy your computer, void warrany, eat cats and burn your flowers. The developer disclaim every damange caused from the usage of this program.", "Close");
}

void OTools::on_actionAbout_triggered()
{
    QMessageBox::about(this,tr("About OTools"),"©2014 Joey Rizzoli (@linuxx)\nSources: https://github.com/linuxxxxx/OTools\nOTools is an opensource software that has the goal to provide a fast, safe and user friendly tool to manage your Oppo or OnePlus Device.");
}

void OTools::on_actionUpdate_triggered()
{
    QMessageBox::information(this,tr("Update"),"Click Start to update OTools","OK");
    /*TODO:
     * download by using a json file or an xml from github?
     */
}

void OTools::on_f5R_clicked()
{
    device="find5";
    ui->modbox->setEnabled(true);
    ui->recbox->setEnabled(true);
    ui->filebox->setEnabled(true);
    ui->backbox->setEnabled(true);
    ui->label->setVisible(false);
    ui->UnlockB->setEnabled(false);
    ui->LockB->setEnabled(false);
    ui->EfsB->setEnabled(false);
    const char *fdevice = qPrintable(device);
    setenv("adbdevice", fdevice, true);
}

void OTools::on_f7R_clicked()
{
    device="find7";
    ui->modbox->setEnabled(true);
    ui->recbox->setEnabled(true);
    ui->filebox->setEnabled(true);
    ui->backbox->setEnabled(true);
    ui->label->setVisible(false);
    ui->UnlockB->setEnabled(false);
    ui->LockB->setEnabled(false);
    ui->EfsB->setEnabled(false);
    const char *fdevice = qPrintable(device);
    setenv("adbdevice", fdevice, true);
}

void OTools::on_opoR_clicked()
{
    device="bacon";
    ui->modbox->setEnabled(true);
    ui->recbox->setEnabled(true);
    ui->filebox->setEnabled(true);
    ui->backbox->setEnabled(true);
    ui->UnlockB->setEnabled(true);
    ui->LockB->setEnabled(true);
    ui->EfsB->setEnabled(true);
    ui->label->setVisible(false);
    const char *fdevice = qPrintable(device);
    setenv("adbdevice", fdevice, true);
}

void OTools::on_n1R_clicked()
{
    device="n1";
    ui->modbox->setEnabled(true);
    ui->recbox->setEnabled(true);
    ui->filebox->setEnabled(true);
    ui->backbox->setEnabled(true);
    ui->label->setVisible(false);
    ui->UnlockB->setEnabled(false);
    ui->LockB->setEnabled(false);
    ui->EfsB->setEnabled(false);
    const char *fdevice = qPrintable(device);
    setenv("adbdevice", fdevice, true);
}


// Buttons

/* TODO:
 * Check if system() returned 0
 */


//Backup

void OTools::on_BackupB_clicked()
{
    QString backfile=QFileDialog::getSaveFileName(this, tr("Save file"), "", ".ab;;All Files (*.*)");
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Backup", backfile,
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        const char *backupf = qPrintable(backfile);
        setenv("backupf", backupf, true);
        QProcess process;
        QProgressDialog *dialog = new QProgressDialog;
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->setRange(0,0);
        connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
        process.start("adb backup -apk -nosystem -noshared f $backupf");
        dialog->exec();
        QMessageBox::information(this,tr("Backup"),"Done!","OK");
    }
}

void OTools::on_RestoreB_clicked()
{
    QString backfile=QFileDialog::getOpenFileName(this, tr("Choose File"),"~","Backups (*.ab);;All Files (*.*)");
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Restore Backup", backfile,
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        const char *backupf = qPrintable(backfile);
        setenv("backupf", backupf, true);
        QProcess process;
        QProgressDialog *dialog = new QProgressDialog;
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->setRange(0,0);
        connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
        process.start("adb restore $backupf");
        dialog->exec();
        QMessageBox::information(this,tr("Restore Backup"),"Done!","OK");
    }
}

//Files

void OTools::on_PushB_clicked(){
    QString pushfile=QFileDialog::getOpenFileName(this, tr("Choose File"), "~", "All Files (*.*)");
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Push File", pushfile,
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
      const char *file = qPrintable(pushfile);
      setenv("pushfile", file, true);
      QProcess process;
      QProgressDialog *dialog = new QProgressDialog;
      dialog->setAttribute(Qt::WA_DeleteOnClose);
      dialog->setRange(0,0);
      connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
      process.start("adb push $pushfile /sdcard/");
      dialog->exec();
      QMessageBox::information(this,tr("Push File"),"Done!","OK");
    }
}

void OTools::on_PullB_clicked(){
    /* TODO:
     * dunno
     */
}

void OTools::on_CamB_clicked(){
    QString camdir=QFileDialog::getExistingDirectory(this,tr("Choose the destination folder"), "~");
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Import from camera", camdir,
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        const char *out = qPrintable(camdir);
        setenv("camdir", out, true);
        QProcess process;
        QProgressDialog *dialog = new QProgressDialog;
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->setRange(0,0);
        connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
        process.start("adb pull /sdcard/DCIM/Camera $camdir");
        dialog->exec();
        QMessageBox::information(this,tr("Import from camera"),"Done!","OK");
    }
}

//Recovery

void OTools::on_pushButton_3_clicked()
{
    if (ui->BackCheck->isChecked()){
        if (ui->ZipCheck->isChecked()){
            if (ui->WipeCheck->isChecked()){
                //back + zip + wipe
                QString pushfile=QFileDialog::getOpenFileName(this, tr("Choose File"), "~", "Flashable Files (*.zip);;All Files (*.*)");
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "Flash Zip", pushfile,
                                              QMessageBox::Yes|QMessageBox::No);
                if (reply == QMessageBox::Yes) {
                    QProcess process;
                    QProgressDialog *dialog = new QProgressDialog;
                    dialog->setAttribute(Qt::WA_DeleteOnClose);
                    dialog->setRange(0,0);
                    connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
                    process.start("sh res/openrecoveryscript --full");
                    dialog->exec();
                    QMessageBox::information(this,tr("Flasher"),"Done!","OK");
                }
        }
        else {
                //back +zip
                QString pushfile=QFileDialog::getOpenFileName(this, tr("Choose File"), "~", "Flashable Files (*.zip);;All Files (*.*)");
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "Flash Zip", pushfile,
                                              QMessageBox::Yes|QMessageBox::No);
                if (reply == QMessageBox::Yes) {
                    QProcess process;
                    QProgressDialog *dialog = new QProgressDialog;
                    dialog->setAttribute(Qt::WA_DeleteOnClose);
                    dialog->setRange(0,0);
                    connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
                    process.start("sh res/openrecoveryscript --backup-zip");
                    dialog->exec();
                    QMessageBox::information(this,tr("Flasher"),"Done!","OK");
                }
            }
        }
        else{
            if (ui->WipeCheck->isChecked()){
                //backup + wipe
                QProcess process;
                QProgressDialog *dialog = new QProgressDialog;
                dialog->setAttribute(Qt::WA_DeleteOnClose);
                dialog->setRange(0,0);
                connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
                process.start("sh res/openrecoveryscript --backup-data");
                dialog->exec();
                QMessageBox::information(this,tr("Flasher"),"Done!","OK");
            }
            else{
                //backup
                QProcess process;
                QProgressDialog *dialog = new QProgressDialog;
                dialog->setAttribute(Qt::WA_DeleteOnClose);
                dialog->setRange(0,0);
                connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
                process.start("sh res/openrecoveryscript --backup");
                dialog->exec();
                QMessageBox::information(this,tr("Flasher"),"Done!","OK");
            }
        }
    }
    else{
        if (ui->ZipCheck->isChecked()){
            if (ui->WipeCheck->isChecked()){
                //zip + wipe
                QString pushfile=QFileDialog::getOpenFileName(this, tr("Choose File"), "~", "Flashable Files (*.zip);;All Files (*.*)");
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "Flash Zip", pushfile,
                                              QMessageBox::Yes|QMessageBox::No);
                if (reply == QMessageBox::Yes) {
                    QProcess process;
                    QProgressDialog *dialog = new QProgressDialog;
                    dialog->setAttribute(Qt::WA_DeleteOnClose);
                    dialog->setRange(0,0);
                    connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
                    process.start("sh res/openrecoveryscript --data-zip");
                    dialog->exec();
                    QMessageBox::information(this,tr("Flasher"),"Done!","OK");
                }
            }
            else {
                //zip
                QString pushfile=QFileDialog::getOpenFileName(this, tr("Choose File"), "~", "Flashable Files (*.zip);;All Files (*.*)");
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "Flash zip", pushfile,
                                              QMessageBox::Yes|QMessageBox::No);
                if (reply == QMessageBox::Yes) {
                    QProcess process;
                    QProgressDialog *dialog = new QProgressDialog;
                    dialog->setAttribute(Qt::WA_DeleteOnClose);
                    dialog->setRange(0,0);
                    connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
                    process.start("sh res/openrecoveryscript --sideload");
                    dialog->exec();
                    QMessageBox::information(this,tr("Flasher"),"Done!","OK");
                }
            }
        }
        else{
            if (ui->WipeCheck->isChecked()){
                //wipe
                QProcess process;
                QProgressDialog *dialog = new QProgressDialog;
                dialog->setAttribute(Qt::WA_DeleteOnClose);
                dialog->setRange(0,0);
                connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
                process.start("sh res/openrecoveryscript --data");
                dialog->exec();
                QMessageBox::information(this,tr("Flasher"),"Done!","OK");
            }
    }
    }
        if (!ui->WipeCheck->isChecked())
            ui->WipeCheck->setCheckState(Qt::Unchecked);
        if (!ui->ZipCheck->isChecked())
            ui->ZipCheck->setCheckState(Qt::Unchecked);
        if (!ui->BackCheck->isChecked())
            ui->BackCheck->setCheckState(Qt::Unchecked);
}

// Advanced stuffs

//MOD

void OTools::on_UnlockB_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, "Unlock Bootloader", "You want to unlock the bootloader,\nthis operation will erase all your personal content such as photos, apps and music, a backup is recommend!\nThis operation may brick your device if something goes wrong.\nAre you sure you want to unlock your device?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QProcess process;
        QProgressDialog *dialog = new QProgressDialog;
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->setRange(0,0);
        connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
        process.start("adb reboot bootloader && fastboot devices && fastboot oem unlock");
        dialog->exec();
        QMessageBox::information(this,tr("Unlock Bootloader"),"Wait until the device completes the operation.","Done");
    }
}

void OTools::on_LockB_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, "Lock Bootloader", "You want to lock the bootloader, you won't be able to boot or flash img files until you'll re-unlock it! You won't loose any data.\n This operation may brick your device if something goes wrong.\nAre you sure you want to unlock your device?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QProcess process;
        QProgressDialog *dialog = new QProgressDialog;
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->setRange(0,0);
        connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
        process.start("adb reboot bootloader && fastboot devices && fastboot oem lock");
        dialog->exec();
      QMessageBox::information(this,tr("Lock Bootloader"),"Done!","OK");
    }
}

void OTools::on_FBootB_clicked()
{
    QString fbboot=QFileDialog::getOpenFileName(
                this,
                tr("Choose File"),
                "~"
                "IMG files (*.img);;All Files (*.*)"
                );
    QMessageBox::information(this,tr("Fastboot Boot"),fbboot,"OK");
    const char *ffbboot = qPrintable(fbboot);
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Fastboot Boot", "Do you want to sideload/boot an img file from your computer?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        setenv("ffbboot", ffbboot, true);
        QProcess process;
        QProgressDialog *dialog = new QProgressDialog;
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->setRange(0,0);
        connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
        process.start("adb reboot bootloader && fastboot devices && fastboot boot $ffbboot");
        dialog->exec();
        QMessageBox::information(this,tr("Fastboot Boot"),"Done!","OK");
    }
}

void OTools::on_FlashBootB_clicked()
{
    QString fboot=QFileDialog::getOpenFileName(
                this,
                tr("Choose File"),
                "~"
                "IMG files (*.img);;All Files (*.*)"
                );
    QMessageBox::information(this,tr("Kernel Installer"),fboot,"OK");
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Kernel Installer", "Do you want to install a new kernel from img?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        const char *ffboot = qPrintable(fboot);
        setenv("ffboot", ffboot, true);
        QProcess process;
        QProgressDialog *dialog = new QProgressDialog;
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->setRange(0,0);
        connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
        process.start("adb reboot bootloader && fastboot devices && fastboot flash boot $ffboot");
        dialog->exec();
        QMessageBox::information(this,tr("Kernel Installer"),"Done!","OK");
    }
}

void OTools::on_RecoveryB_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Recovery Installer", "Do you already have a recovery for your device on the pc?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QString recovery=QFileDialog::getOpenFileName(
                    this,
                    tr("Choose File"),
                    "~"
                    "IMG files (*.img);;All Files (*.*)"
                    );
        QMessageBox::information(this,tr("Recovery Installer"),recovery,"OK");
        const char *frecovery = qPrintable(recovery);
        setenv("frecovery", frecovery, true);
    } else {
        char* recovery("res/$adbdevice/recovery.img");
        setenv("frecovery", recovery, true);
    }
    QProcess process;
    QProgressDialog *dialog = new QProgressDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setRange(0,0);
    connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
    process.start("adb reboot bootloader && fastboot devices && fastboot flash recovery $recovery && fastboot reboot");
    dialog->exec();
    QMessageBox::information(this,tr("Recovery Installer"),"Done!","OK");
}

void OTools::on_FBFlashB_clicked()
{
    /* TODO >>LATER<<:
     * ask partition name (choose from an array?)
     * Filepicker
     * flash
     */
}

void OTools::on_RootB_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, "Rooter", "This operation will root your device.\nBootloader must be unlocked otherwhise it fail.\nDo you want to continue?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        //TODO: add a unlocked-checker using fastboot oem device-info | grep 'Device unlocked: '
        const char *updatezip("res/root.zip");
        setenv("updatezip", updatezip, true);
        QProcess process;
        QProgressDialog *dialog = new QProgressDialog;
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->setRange(0,0);
        connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
        process.start("adb reboot bootloader && fastboot devices && fastboot boot res/$adbdevice/recovery.img && sh res/openrecovery.sh");
        dialog->exec();
        // TODO: find a better way to inject openrecovery commands
        QMessageBox::information(this,tr("Rooter"),"Done!","OK");
    }
}

void OTools::on_LogoB_clicked()
{
    QString logo=QFileDialog::getOpenFileName(
                this,
                tr("Choose File"),
                "~"
                "Logo files (*.bin);;All Files (*.*)"
                );
    QMessageBox::information(this,tr("Logo Changer"),logo,"OK");
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Logo Changer", "This operation will change your bootlogo (Your bootloader needs to be unlocked otherwhise it will fail).\nDo you want to continue?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        const char *flogo = qPrintable(logo);
        setenv("flogo", flogo, true);
        QProcess process;
        QProgressDialog *dialog = new QProgressDialog;
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->setRange(0,0);
        connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
        process.start("adb reboot bootloader && fastboot devices && fastboot flash LOGO $flogo && fastboot reboot");
        dialog->exec();
        QMessageBox::information(this,tr("Logo Changer"),"Done!","OK");
    }
}

void OTools::on_EfsB_clicked()
{
    QMessageBox::information(this,tr("EFS Backup"),"You need root access in order to backup efs","Continue");
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "EFS Backup", "This operation will backup efs on the top of your sdcard.\nYou need root access otherwhise it will fail\nDo you want to continue?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QProcess process;
        QProgressDialog *dialog = new QProgressDialog;
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->setRange(0,0);
        connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
        process.start("adb root && adb shell 'dd if=/dev/block/mmcblk0p10 of=/sdcard/modemst1.bin bs=512' && adb shell 'dd if=/dev/block/mmcblk0p11 of=/sdcard/modemst2.bin bs=512'");
        dialog->exec();
      QMessageBox::information(this,tr("EFS Backup"),"Done!","OK");
    }
}

void OTools::on_SRECB_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Screen Recorder", "You need android 4.4.x+ in order to record your screen.\nUnPlug the device when you want to stop the registration.\nThe program will freeze until it's working.\n Do you want to start?)",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QMessageBox::information(this,tr("Screen Recorder"), "UnPlug the device when you want to stop the registration.\nAll the other features will be disabled!");
        QProcess process;
        QProgressDialog *dialog = new QProgressDialog;
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->setRange(0,0);
        connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
        process.start("adb shell screenrecord /sdcard/video.mp4");
        dialog->exec();
        QMessageBox::information(this,tr("Screen Recorder"),"Done!","OK");
    }
}

void OTools::on_ShellB_clicked()
{
    /* TODO:
     * open xterm with adb shell << I don't like this
     */
}

void OTools::on_ApkB_clicked()
{
    QString apk=QFileDialog::getOpenFileName(
                this,
                tr("Choose File"),
                "~"
                "Apk files (*.apk);;All Files (*.*)"
                );
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Apk Installer",apk ,
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        const char *fapk = qPrintable(apk);
        setenv("fapk", fapk, true);
        QProcess process;
        QProgressDialog *dialog = new QProgressDialog;
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->setRange(0,0);
        connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
        process.start("adb install $fapk");
        dialog->exec();
        QMessageBox::information(this,tr("Apk Installer"),"Done!","OK");
    }
}

void OTools::on_RootC_clicked()
{
    system("xterm -e 'sudo ./O-Tools &>/dev/null'");
}

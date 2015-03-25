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

#ifdef __WIN32__
#include <QProcessEnvironment>
#endif

QString device("unknow");

OTools::OTools(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OTools)
{
    ui->setupUi(this);
#ifdef __WIN32__
    env = QProcessEnvironment::systemEnvironment();
#endif
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
    ui->partitionbox->setEnabled(true);
    const char *fdevice = qPrintable(device);
#ifndef __WIN32__
    setenv("adbdevice", fdevice, true);
#else
    env.insert("adbdevice", fdevice);
#endif
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
    ui->partitionbox->setEnabled(false);
    const char *fdevice = qPrintable(device);
#ifndef __WIN32__
    setenv("adbdevice", fdevice, true);
#else
    env.insert("adbdevice", fdevice);
#endif
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
    ui->partitionbox->setEnabled(false);
    const char *fdevice = qPrintable(device);
#ifndef __WIN32__
    setenv("adbdevice", fdevice, true);
#else
    env.insert("adbdevice", fdevice);
#endif
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
    ui->partitionbox->setEnabled(false);
    const char *fdevice = qPrintable(device);
#ifndef __WIN32__
    setenv("adbdevice", fdevice, true);
#else
    env.insert("adbdevice", fdevice);
#endif
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
#ifndef __WIN32__
        setenv("backupf", backupf, true);
#else
        env.insert("backupf", backupf);
#endif
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
#ifndef __WIN32__
        setenv("backupf", backupf, true);
#else
        env.insert("backupf", backupf);
#endif
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
#ifndef __WIN32__
      setenv("pushfile", file, true);
#else
      env.insert("pushfile", file);
#endif
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
#ifndef __WIN32__
        setenv("camdir", out, true);
#else
        env.insert("camdir", out);
#endif
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
#ifndef __WIN32__
        setenv("ffbboot", ffbboot, true);
#else
        env.insert("ffbboot", ffbboot);
#endif
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
#ifndef __WIN32__
        setenv("ffboot", ffboot, true);
#else
        env.insert("ffboot", ffboot);
#endif
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
#ifndef __WIN32__
        setenv("frecovery", frecovery, true);
#else
        env.insert("frecovery", frecovery);
#endif
    } else {
        const char* recovery("res/$adbdevice/recovery.img");
#ifndef __WIN32__
        setenv("frecovery", recovery, true);
#else
        env.insert("frecovery", recovery);
#endif
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
#ifndef __WIN32__
        setenv("updatezip", updatezip, true);
#else
        env.insert("updatezip", updatezip);
#endif
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
#ifndef __WIN32__
        setenv("flogo", flogo, true);
#else
        env.insert("flogo", flogo);
#endif
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
#ifndef __WIN32__
        setenv("fapk", fapk, true);
#else
        env.insert("fapk", fapk);
#endif
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

void OTools::on_IncreaseSystemPartion_toggled(bool checked)
{
    if(checked) {
        ui->UserDataPartitionCmbBox->setEnabled(true);
        ui->btnGrowParitionExecute->setEnabled(true);
    } else {
        ui->UserDataPartitionCmbBox->setEnabled(false);
        ui->btnGrowParitionExecute->setEnabled(false);
    }
}

void OTools::prepareDevice4PartitionUpdate() {
    /* Reboot into recovery and wait for adb to get recognized */
    system("adb reboot recovery");
    QMessageBox::information(this, tr("Waiting for Recovery boot..."), "Click PROCEED when the phone has booted into TWRP recovery properly. NOT BEFORE THAT...", "PROCEED");

    /* Assume parted, make2fs and tune2fs are present in /sbin
       thorough TWRP recovery. Unmount all mounted partitions
       in recovery */
    system("adb shell \"umount /sdcard; umount /emmc; umount /data; umount /dev/block/mmcblk0p29; umount /dev/block/mmcblk0p22;\"");

    /* Now we run parted with -s and pray it works ! */
    system("adb shell \"parted -s /dev/block/mmcblk0 rm 30; parted -s /dev/block/mmcblk0 rm 29;"
                       "parted -s /dev/block/mmcblk0 rm 28; parted -s /dev/block/mmcblk0 rm 27 \"");
    system("adb shell \"parted -s /dev/block/mmcblk0 rm 26; parted -s /dev/block/mmcblk0 rm 25;"
                       "parted -s /dev/block/mmcblk0 rm 24; parted -s /dev/block/mmcblk0 rm 23 \"");
    system("adb shell \"parted -s /dev/block/mmcblk0 rm 22; parted -s /dev/block/mmcblk0 rm 21;"
                       "parted -s /dev/block/mmcblk0 rm 20 \"");

}

/* Used to do the postpartitioning update... */
void OTools::postPartitionProcessing() {
    /* Format the newly created partitions as needed with sdcard as fat32 */
    system("adb shell \"mke2fs -t ext4 -m 0 -L userdata /dev/block/mmcblk0p20;"
                       "tune2fs -c 0 -i -1 -C -1 /dev/block/mmcblk0p20;"
                       "mke2fs -t ext4 -m 0 -L persist /dev/block/mmcblk0p21;"
                       "tune2fs -c 0 -i -1 -C -1 /dev/block/mmcblk0p21 \"");
    system("adb shell \"mke2fs -t ext4 -m 0 -L cache /dev/block/mmcblk0p22;"
                       "tune2fs -c 0 -i -1 -C -1 /dev/block/mmcblk0p22;"
                       "mke2fs -t ext4 -m 0 -L sdcard /dev/block/mmcblk0p29;"
                       "tune2fs -c 0 -i -1 -C -1 /dev/block/mmcblk0p29;"
                       "mkdosfs -n sdcard -F 32 /dev/block/mmcblk0p29;"
                       "mount -t vfat /dev/block/mmcblk0p29 /sdcard \"");

    /* Now restore /persist partition */
    system("adb push find5/mmcblk0p21_persist_ext4.img /sdcard/");
    system("adb push find5/twrp-2.8.5.0-find5.img /sdcard/");
    system("adb shell \"dd if=/sdcard/mmcblk0p21_persist_ext4.img of=/dev/block/mmcblk0p21;"
                       "dd if=/sdcard/twrp-2.8.5.0-find5.img of=/dev/block/mmcblk0p24; \"");
}

/* We do it on the main UI Thread since this is a non-cancellable operation
 * REF: http://www.oppoforums.com/threads/guide-resizing-internal-storage-on-find-5-32gb.8361/page-32#post-310870
*/
void OTools::on_btnGrowParitionExecute_clicked()
{
    prepareDevice4PartitionUpdate();
    switch(ui->UserDataPartitionCmbBox->currentIndex()) {
        case 0: {
            /* 06 GB {6.0 GiB / 21.3 GiB} Selected
06 GB {6.0 GiB / 21.3 GiB}
Code:
20      2588672s   15171583s  12582912s  ext4         userdata
21      15171584s  15187967s  16384s     ext4         persist
22      15187968s  16236543s  1048576s   ext4         cache
23      16236544s  16238591s  2048s                   misc
24      16252928s  16273407s  20480s                  recovery
25      16285696s  16351231s  65536s                  reserve1
26      16351232s  16367615s  16384s                  reserve2
27      16367616s  16383999s  16384s                  reserve3
28      16384000s  16449535s  65536s                  reserve4
29      16449536s  61071326s  44621791s  fat32        sdcard
*/
            system("adb shell \"parted -s /dev/block/mmcblk0 mkpart primary 2588672s 15171583s;"
                               "parted -s /dev/block/mmcblk0 name 20 userdata;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 15171584s 15187967s;"
                               "parted -s /dev/block/mmcblk0 name 21 persist;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 15187968s 16236543s;"
                               "parted -s /dev/block/mmcblk0 name 22 cache \"");
            system("adb shell \"parted -s /dev/block/mmcblk0 mkpart primary 16236544s 16238591s;"
                               "parted -s /dev/block/mmcblk0 name 23 misc;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 16252928s 16273407s;"
                               "parted -s /dev/block/mmcblk0 name 24 recovery;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 16285696s 16351231s;"
                               "parted -s /dev/block/mmcblk0 name 25 reserve1 \"");
            system("adb shell \"parted -s /dev/block/mmcblk0 mkpart primary 16351232s 16367615s;"
                               "parted -s /dev/block/mmcblk0 name 26 reserve2;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 16367616s 16383999s;"
                               "parted -s /dev/block/mmcblk0 name 27 reserve3;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 16384000s 16449535s;"
                               "parted -s /dev/block/mmcblk0 name 28 reserve4;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 16449536s 100%;"
                               "parted -s /dev/block/mmcblk0 name 29 sdcard \"");
            break;
        }
        case 1: {
/*
07 GB {7.0 GiB / 20.3 GiB}
Code:
20      2588672s   17268735s  14680064s  ext4         userdata
21      17268736s  17285119s  16384s     ext4         persist
22      17285120s  18333695s  1048576s   ext4         cache
23      18333696s  18335743s  2048s                   misc
24      18350080s  18370559s  20480s                  recovery
25      18382848s  18448383s  65536s                  reserve1
26      18448384s  18464767s  16384s                  reserve2
27      18464768s  18481151s  16384s                  reserve3
28      18481152s  18546687s  65536s                  reserve4
29      18546688s  61071326s  42524639s  fat32        sdcard
*/
            system("adb shell \"parted -s /dev/block/mmcblk0 mkpart primary 2588672s 17268735s;"
                               "parted -s /dev/block/mmcblk0 name 20 userdata;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 17268736s 17285119s;"
                               "parted -s /dev/block/mmcblk0 name 21 persist;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 17285120s 18333695s;"
                               "parted -s /dev/block/mmcblk0 name 22 cache \"");
            system("adb shell \"parted -s /dev/block/mmcblk0 mkpart primary 18333696s 18335743s;"
                               "parted -s /dev/block/mmcblk0 name 23 misc;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 18350080s 18370559s;"
                               "parted -s /dev/block/mmcblk0 name 24 recovery;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 18382848s 18448383s;"
                               "parted -s /dev/block/mmcblk0 name 25 reserve1 \"");
            system("adb shell \"parted -s /dev/block/mmcblk0 mkpart primary 18448384s 18464767s;"
                               "parted -s /dev/block/mmcblk0 name 26 reserve2;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 18464768s 18481151s;"
                               "parted -s /dev/block/mmcblk0 name 27 reserve3;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 18481152s 18546687s;"
                               "parted -s /dev/block/mmcblk0 name 28 reserve4;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 18546688s 100%;"
                               "parted -s /dev/block/mmcblk0 name 29 sdcard \"");
            break;
        }
        case 2: {
/*
08 GB {8.0 GiB / 19.3 GiB}
Code:
20      2588672s   19365887s  16777216s  ext4         userdata
21      19365888s  19382271s  16384s     ext4         persist
22      19382272s  20430847s  1048576s   ext4         cache
23      20430848s  20432895s  2048s                   misc
24      20447232s  20467711s  20480s                  recovery
25      20480000s  20545535s  65536s                  reserve1
26      20545536s  20561919s  16384s                  reserve2
27      20561920s  20578303s  16384s                  reserve3
28      20578304s  20643839s  65536s                  reserve4
29      20643840s  61071326s  40427487s  fat32        sdcard
*/
            system("adb shell \"parted -s /dev/block/mmcblk0 mkpart primary 2588672s 19365887s;"
                               "parted -s /dev/block/mmcblk0 name 20 userdata;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 19365888s 19382271s;"
                               "parted -s /dev/block/mmcblk0 name 21 persist;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 19382272s 20430847s;"
                               "parted -s /dev/block/mmcblk0 name 22 cache \"");
            system("adb shell \"parted -s /dev/block/mmcblk0 mkpart primary 20430848s 20432895s;"
                               "parted -s /dev/block/mmcblk0 name 23 misc;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 20447232s 20467711s;"
                               "parted -s /dev/block/mmcblk0 name 24 recovery;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 20480000s 20545535s;"
                               "parted -s /dev/block/mmcblk0 name 25 reserve1 \"");
            system("adb shell \"parted -s /dev/block/mmcblk0 mkpart primary 20545536s 20561919s;"
                               "parted -s /dev/block/mmcblk0 name 26 reserve2;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 20561920s 20578303s;"
                               "parted -s /dev/block/mmcblk0 name 27 reserve3;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 20578304s 20643839s;"
                               "parted -s /dev/block/mmcblk0 name 28 reserve4;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 20643840s 100%;"
                               "parted -s /dev/block/mmcblk0 name 29 sdcard \"");
            break;
        }
        case 3: {
/*
09 GB {9.0 GiB / 18.3 GiB}
Code:
20      2588672s   21463039s  18874368s  ext4         userdata
21      21463040s  21479423s  16384s     ext4         persist
22      21479424s  22527999s  1048576s   ext4         cache
23      22528000s  22530047s  2048s                   misc
24      22544384s  22564863s  20480s                  recovery
25      22577152s  22642687s  65536s                  reserve1
26      22642688s  22659071s  16384s                  reserve2
27      22659072s  22675455s  16384s                  reserve3
28      22675456s  22740991s  65536s                  reserve4
29      22740992s  61071326s  38330335s  fat32        sdcard
*/
            system("adb shell \"parted -s /dev/block/mmcblk0 mkpart primary 2588672s 21463039s;"
                               "parted -s /dev/block/mmcblk0 name 20 userdata;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 21463040s 21479423s;"
                               "parted -s /dev/block/mmcblk0 name 21 persist;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 21479424s 22527999s;"
                               "parted -s /dev/block/mmcblk0 name 22 cache \"");
            system("adb shell \"parted -s /dev/block/mmcblk0 mkpart primary 22528000s 22530047s;"
                               "parted -s /dev/block/mmcblk0 name 23 misc;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 22544384s 22564863s;"
                               "parted -s /dev/block/mmcblk0 name 24 recovery;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 22577152s 22642687s;"
                               "parted -s /dev/block/mmcblk0 name 25 reserve1 \"");
            system("adb shell \"parted -s /dev/block/mmcblk0 mkpart primary 22642688s 22659071s;"
                               "parted -s /dev/block/mmcblk0 name 26 reserve2;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 22659072s 22675455s;"
                               "parted -s /dev/block/mmcblk0 name 27 reserve3;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 22675456s 22740991s;"
                               "parted -s /dev/block/mmcblk0 name 28 reserve4;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 22740992s 100%;"
                               "parted -s /dev/block/mmcblk0 name 29 sdcard \"");
            break;
        }
        case 4: {
/*
10 GB {10.0 GiB / 17.3 GiB}
Code:
20      2588672s   23560191s  20971520s  ext4         userdata
21      23560192s  23576575s  16384s     ext4         persist
22      23576576s  24625151s  1048576s   ext4         cache
23      24625152s  24627199s  2048s                   misc
24      24641536s  24662015s  20480s                  recovery
25      24674304s  24739839s  65536s                  reserve1
26      24739840s  24756223s  16384s                  reserve2
27      24756224s  24772607s  16384s                  reserve3
28      24772608s  24838143s  65536s                  reserve4
29      24838144s  61071326s  36233183s  fat32        sdcard
*/
            system("adb shell \"parted -s /dev/block/mmcblk0 mkpart primary 2588672s 23560191s;"
                               "parted -s /dev/block/mmcblk0 name 20 userdata;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 23560192s 23576575s;"
                               "parted -s /dev/block/mmcblk0 name 21 persist;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 23576576s 24625151s;"
                               "parted -s /dev/block/mmcblk0 name 22 cache \"");
            system("adb shell \"parted -s /dev/block/mmcblk0 mkpart primary 24625152s 24627199s;"
                               "parted -s /dev/block/mmcblk0 name 23 misc;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 24641536s 24662015s;"
                               "parted -s /dev/block/mmcblk0 name 24 recovery;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 24674304s 24739839s;"
                               "parted -s /dev/block/mmcblk0 name 25 reserve1 \"");
            system("adb shell \"parted -s /dev/block/mmcblk0 mkpart primary 24739840s 24756223s;"
                               "parted -s /dev/block/mmcblk0 name 26 reserve2;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 24756224s 24772607s;"
                               "parted -s /dev/block/mmcblk0 name 27 reserve3;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 24772608s 24838143s;"
                               "parted -s /dev/block/mmcblk0 name 28 reserve4;"
                               "parted -s /dev/block/mmcblk0 mkpart primary 24838144s 100%;"
                               "parted -s /dev/block/mmcblk0 name 29 sdcard \"");
            break;
        }

    }
    postPartitionProcessing();
    QMessageBox::information(this,tr("Partition Updater"),"Brave Soul! All should be done, if not RTFM :P","OK");
}

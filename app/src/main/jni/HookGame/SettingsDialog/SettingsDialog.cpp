//
// Created by Administrator on 2024/4/21.
//


Sexy::Checkbox *m3DAccleratedCheckbox = NULL;

void (*old_SettingsDialog_AddedToManager)(SettingsDialog *settingsDialog, int *manager);

void SettingsDialog_AddedToManager(SettingsDialog *settingsDialog, int *manager) {
    old_SettingsDialog_AddedToManager(settingsDialog, manager);
    LawnApp *lawnApp = (LawnApp *) *gLawnApp_Addr;
    m3DAccleratedCheckbox = MakeNewCheckbox(1024, &settingsDialog->mCheckboxListener, settingsDialog, Sexy_SexyAppBase_Is3DAccelerated(lawnApp));
    Sexy_Widget_Resize(m3DAccleratedCheckbox, 80, 260, 300, 50);
    Sexy::Widget* mSoundSlider = settingsDialog->mSoundSlider;
    Sexy::Widget* mBackButton = settingsDialog->mBackButton;
    mSoundSlider->mFocusLinks[1] = m3DAccleratedCheckbox;
    m3DAccleratedCheckbox->mFocusLinks[1] = mBackButton;
    mBackButton->mFocusLinks[0] = m3DAccleratedCheckbox;
    m3DAccleratedCheckbox->mFocusLinks[0] = mSoundSlider;
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))settingsDialog->vTable + 6))(settingsDialog, m3DAccleratedCheckbox); // AddWidget()
}

void (*old_SettingsDialog_RemovedFromManager)(SettingsDialog *settingsDialog, int *manager);

void SettingsDialog_RemovedFromManager(SettingsDialog *settingsDialog, int *manager) {
    old_SettingsDialog_RemovedFromManager(settingsDialog, manager);
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))settingsDialog->vTable + 7))(settingsDialog, m3DAccleratedCheckbox); // RemoveWidget()
}

void (*old_SettingsDialog_Delete2)(SettingsDialog *settingsDialog);

void SettingsDialog_Delete2(SettingsDialog *settingsDialog) {
    old_SettingsDialog_Delete2(settingsDialog);
//    Sexy_Checkbox_Delete(m3DAccleratedCheckbox); // 在安卓4.2上，这么Delete会闪退
    (*((void (__fastcall **)(Sexy::Widget *))m3DAccleratedCheckbox->vTable + 1))(m3DAccleratedCheckbox);// Delete() ，用这种方式Delete在安卓4.2上就不会闪退，虽然我也不知道为什么会这样
    m3DAccleratedCheckbox = NULL;
}

void (*old_SettingsDialog_Draw)(SettingsDialog *settingsDialog, Sexy::Graphics *graphics);

void SettingsDialog_Draw(SettingsDialog *settingsDialog, Sexy::Graphics *graphics) {
    old_SettingsDialog_Draw(settingsDialog, graphics);

    Color color = {107,110,145,255};
    if (settingsDialog->mFocusedChildWidget == m3DAccleratedCheckbox) {
        color.mRed = 0;
        color.mGreen = 255;
        color.mBlue = 0;
        color.mAlpha = 255;
    }
    int holder[1];
    Sexy_Graphics_SetFont(graphics,*Sexy_FONT_DWARVENTODCRAFT18_Addr);
    Sexy_Graphics_SetColor(graphics,&color);
    TodStringTranslate(holder,"[OPTIONS_3D_ACCELERATION]");
    Sexy_Graphics_DrawString(graphics, holder, m3DAccleratedCheckbox->mX + 80, m3DAccleratedCheckbox->mY + 20);
    Sexy_String_Delete(holder);
}

void SettingsDialog_CheckboxChecked(SettingsDialog *settingsDialog, int id, bool isChecked){
    if (id == 1024) {
        LawnApp *lawnApp = (LawnApp *) *gLawnApp_Addr;
        Sexy_SexyAppBase_Set3DAccelerated(lawnApp, isChecked);
    }
}

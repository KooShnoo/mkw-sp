#include "LicenseSelectPage.h"

#include "../system/SaveManager.h"

static const Page_vt s_LicenseSelectPage_vt;

static void onBack(InputHandler *this, u32 localPlayerId) {
    UNUSED(localPlayerId);

    LicenseSelectPage *page = container_of(this, LicenseSelectPage, onBack);
    page->replacement = 0x57; // TODO enum
    Page_startReplace(page, PAGE_ANIMATION_PREV, 0.0f);
}

static const InputHandler_vt onBack_vt = {
    .handle = onBack,
};

static LicenseSelectPage *my_LicenseSelectPage_ct(LicenseSelectPage *this) {
    Page_ct(this);
    this->vt = &s_LicenseSelectPage_vt;

    MultiControlInputManager_ct(&this->inputManager);
    CtrlMenuPageTitleText_ct(&this->pageTitleText);
    CtrlMenuBackButton_ct(&this->backButton);
    for (u32 i = 0; i < ARRAY_SIZE(this->licenseButtons); i++) {
        LicenseSelectButton_ct(&this->licenseButtons[i]);
    }
    this->onBack.vt = &onBack_vt;

    return this;
}

PATCH_B(LicenseSelectPage_ct, my_LicenseSelectPage_ct);

static void LicenseSelectPage_dt(Page *base, s32 type) {
    LicenseSelectPage *this = (LicenseSelectPage *)base;

    for (u32 i = ARRAY_SIZE(this->licenseButtons); i --> 0;) {
        LicenseSelectButton_dt(&this->licenseButtons[i], -1);
    }
    CtrlMenuBackButton_dt(&this->backButton, -1);
    CtrlMenuPageTitleText_dt(&this->pageTitleText, -1);
    MultiControlInputManager_dt(&this->inputManager, -1);

    Page_dt(this, 0);
    if (type > 0) {
        delete(this);
    }
}

static s32 LicenseSelectPage_getReplacement(Page *base) {
    LicenseSelectPage *this = (LicenseSelectPage *)base;

    return this->replacement;
}

static void LicenseSelectPage_onInit(Page *base) {
    LicenseSelectPage *this = (LicenseSelectPage *)base;

    MultiControlInputManager_init(&this->inputManager, 0x1, false);
    this->baseInputManager = &this->inputManager;
    MultiControlInputManager_setPointerMode(&this->inputManager, 0x1);

    Page_initChildren(this, 2 + ARRAY_SIZE(this->licenseButtons));
    Page_insertChild(this, 0, &this->pageTitleText, 0);
    Page_insertChild(this, 1, &this->backButton, 0);
    for (u32 i = 0; i < ARRAY_SIZE(this->licenseButtons); i++) {
        Page_insertChild(this, 2 + i, &this->licenseButtons[i], 0);
    }

    CtrlMenuPageTitleText_load(&this->pageTitleText, false);
    PushButton_load(&this->backButton, "button", "Back", "ButtonBackPopup", 0x1, false, true);
    for (u32 i = 0; i < ARRAY_SIZE(this->licenseButtons); i++) {
        LicenseSelectButton_load(&this->licenseButtons[i], i);
    }

    MultiControlInputManager_setHandler(&this->inputManager, INPUT_ID_BACK, &this->onBack, false, false);

    CtrlMenuPageTitleText_setMessage(&this->pageTitleText, 0x838, NULL);
}

static void LicenseSelectPage_onActivate(Page *base) {
    LicenseSelectPage *this = (LicenseSelectPage *)base;

    u32 index = s_saveManager->spCurrentLicense < 0 ? 0 : s_saveManager->spCurrentLicense;
    PushButton_selectDefault(&this->licenseButtons[index], 0);

    this->replacement = -1; // TODO enum
}

static const Page_vt s_LicenseSelectPage_vt = {
    .dt = LicenseSelectPage_dt,
    .vf_0c = &Page_vf_0c,
    .getReplacement = LicenseSelectPage_getReplacement,
    .vf_14 = &Page_vf_14,
    .vf_18 = &Page_vf_18,
    .changeSection = Page_changeSection,
    .vf_20 = &Page_vf_20,
    .push = Page_push,
    .onInit = LicenseSelectPage_onInit,
    .onDeinit = Page_onDeinit,
    .onActivate = LicenseSelectPage_onActivate,
    .vf_34 = &Page_vf_34,
    .vf_38 = &Page_vf_38,
    .vf_3c = &Page_vf_3c,
    .vf_40 = &Page_vf_40,
    .vf_44 = &Page_vf_44,
    .vf_48 = &Page_vf_48,
    .vf_4c = &Page_vf_4c,
    .vf_50 = &Page_vf_50,
    .onRefocus = Page_onRefocus,
    .vf_58 = &Page_vf_58,
    .vf_5c = &Page_vf_5c,
    .vf_60 = &Page_vf_60,
};

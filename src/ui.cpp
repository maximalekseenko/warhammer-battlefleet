#include "ui.h"



namespace ui
{
    UiComponent::UiComponent(UiComponent* __parent, int __x, int __y, int __w, int __h)
    {
        this->_parent = __parent;
        this->x(__x);
        this->y(__y);
        this->w(__w);
        this->h(__h);
    }
    UiComponent::UiComponent(UiComponent* __parent, int __x, int __y, double __Pw, double __Ph)
    {
        this->_parent = __parent;
        this->x(__x);
        this->y(__y);
        this->Pw(__Pw);
        this->Ph(__Ph);
    }
    UiComponent::UiComponent(UiComponent* __parent, double __Px, double __Py, int __w, int __h)
    {
        this->_parent = __parent;
        this->Px(__Px);
        this->Py(__Py);
        this->w(__w);
        this->h(__h);
    }
    UiComponent::UiComponent(UiComponent* __parent, double __Px, double __Py, double __Pw, double __Ph)
    {
        this->_parent = __parent;
        this->Px(__Px);
        this->Py(__Py);
        this->Pw(__Pw);
        this->Ph(__Ph);
    }

    const int UiComponent::x()
    { 
        if (this->_isXinP)
            return this->_parent->x() * this->_Px;
        else return this->_x;
    }
    void UiComponent::x(int __value) 
    {
        this->_x = __value;
        this-> _isXinP = false;
    }

    const int UiComponent::y() 
    { 
        if (this->_isYinP)
            return this->_parent->y() * this->_Py;
        else return this->_y;
    }
    void UiComponent::y(int __value) 
    {
        this->_y = __value;
        this-> _isYinP = false;
    }

    const double UiComponent::Px() 
    {
        if (this->_isXinP)
            return this->_Px;
        else return double(this->_parent->x()) / this->_x;
    }
    void UiComponent::Px(double __value) 
    {
        this->_Px = __value;
        this-> _isXinP = true;
    }

    const double UiComponent::Py() 
    {
        if (this->_isYinP)
            return this->_Py;
        else return double(this->_parent->y()) / this->_y;
    }
    void UiComponent::Py(double __value) 
    {
        this->_Py = __value;
        this-> _isYinP = true;
    }

    const int UiComponent::w() 
    {
        if (this->_isWinP)
            return this->_parent->w() * this->_Pw;
        else return this->_w;
    }
    void UiComponent::w(int __value) 
    {
        this->_w = __value;
        this-> _isWinP = false;
    }

    const int UiComponent::h() 
    {
        if (this->_isHinP)
            return this->_parent->h() * this->_Ph;
        else return this->_h;
    }
    void UiComponent::h(int __value) 
    {
        this->_h = __value;
        this-> _isHinP = false;
    }

    const double UiComponent::Pw()
    {
        if (this->_isWinP)
            return this->_Pw;
        else return double(this->_parent->w()) / this->_w;
    }
    void UiComponent::Pw(double __value) 
    {
        this->_Pw = __value;
        this-> _isWinP = true;
    }

    const double UiComponent::Ph() 
    {
        if (this->_isHinP)
            return this->_Ph;
        else return double(this->_parent->h()) / this->_h;
    }
    void UiComponent::Ph(double __value) 
    {
        this->_Ph = __value;
        this-> _isHinP = true;
    }

    UiComponent* _mainmenu;
    UiComponent* _mainsettingsmenu;
    UiComponent* _fleetmenu;
    UiComponent* _lobbymenu;
    UiComponent* _lobbysettingsmenu;
    UiComponent* _lobbyendmenu;

    UiComponent* mainmenu() { return _mainmenu; }

    int Init(int arg, const char** argv)
    {
        // main menu
        // _mainmenu = new UiComponent(NULL, 0, 0, 1.0, 1.0);
        // _mainmenu.components = 
        // {
        //     UiComponent { // Line
        //         .x = 0  , .y = 0  ,
        //         .w = 0.9, .h = 0.01,
        //         .align_x=1, .align_y=0,
        //     }
// 
        // };
    }

    int Deinit()
    {
        delete _mainmenu;
    }
    
}

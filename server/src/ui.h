#pragma once



#include <vector>



namespace ui
{
    int Init(int arg, const char** argv);
    int Deinit();

    struct UiComponent
    {
        std::vector<UiComponent> components;
        public: // ----------CONSTRUCTORS / DESTRUCTORS----------
            UiComponent(UiComponent* __parent, int _x, int _y, int _w, int _h);
            UiComponent(UiComponent* __parent, int _x, int _y, double _Pw, double _Ph);
            UiComponent(UiComponent* __parent, double _Px, double _Py, int _w, int _h);
            UiComponent(UiComponent* __parent, double _Px, double _Py, double _Pw, double _Ph);
        public: // ----------MEMBER ACCESS----------
            const int x();
            void x(int __value);

            const int y();
            void y(int __value);

            const double Px();
            void Px(double __value);

            const double Py();
            void Py(double __value);

            const int w();
            void w(int __value);

            const int h();
            void h(int __value);

            const double Pw();
            void Pw(double __value);

            const double Ph();
            void Ph(double __value);
        private: // ----------MEMBERS----------
            UiComponent* _parent;
            int _offset_x, _offset_y;

            double _Px, _Py; int _x, _y; bool _isXinP, _isYinP;
            double _Pw, _Ph; int _w, _h; bool _isWinP, _isHinP;

            int align_x = 0, align_y = 0;
    };

    UiComponent* mainmenu();
}

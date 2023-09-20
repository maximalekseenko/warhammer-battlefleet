gui = require('nw.gui');
gui.Window.get().showDevTools();

LoadData();
console.log(Data);

jQuery(function() {
    OpenMenu("mainmenu.html");
})

function Quit()
{
    gui.App.quit();
}
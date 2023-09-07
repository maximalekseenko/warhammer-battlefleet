/**
 * 
 * @param {string} name 
 */
function OpenMenu(name)
{
    $( ".menu" ).load(`./menus/${name}`);
}
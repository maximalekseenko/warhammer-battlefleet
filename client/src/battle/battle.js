var selectedVesselId = -1;
var battleData = {
    "vessels":[
        {
            "player":0,
            "fraction":"imperial",
            "type":1,
            "selects":[0,0],
            "delays":[0,0],
            "position":[10,10,0]
        },{
            "player":0,
            "fraction":"imperial",
            "type":1,
            "selects":[0,0],
            "delays":[0,0],
            "position":[10,20,0]
        },
    ]
}


function UpdateVisuals()
{
    $( '.battle-vessels' ).html('');

    battleData.vessels.forEach(vesselData => {
        console.log($( '.battle-vessels' ).append(
            `<img class='battle-vessel' name='0' src='./img/${vesselData.fraction}-vessel-${vesselData.type}.png'>`
        ))
    });
}




function SelectVessel()
{

}


function Action()
{

}
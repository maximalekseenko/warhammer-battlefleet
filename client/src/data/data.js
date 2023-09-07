var Data = [
    {
        "name": "",

        "vessels":
        [
            {
                "name": "",
                "id": 0,
                "img": "",

                "type": 0,
                "hits": 0,
                "shields": 0,
                "armour": 0,
                "turrents": 0,

                "speed": 0,
                "turns": 0,

                "armaments-selections": [ [ "" ] ],
                "armaments":
                [
                    {
                        "selection": 0,
                        "pos": [ 0, 0, 0 ]
                    }
                ]
            }
        ],
        "armaments":
        [

        ]
    }
]


var UserSTC = [
    {
        "id": 0,
        "armaments-selections": [ 0 ]
    }
]

function LoadData()
{
    $.getJSON("./data/data.json").then(function(_data) {Data = _data});
}
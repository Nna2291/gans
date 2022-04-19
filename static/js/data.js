function gett() {
    $.ajax({
        url: "/data",
        type: "get",

        success: function (response) {
            $('div.environment div.variable h3.figure[name=temp]')[0].innerHTML = `${response.temp}<span> °C</span>`;
            $('div.environment div.variable h3.figure[name=elek]')[0].innerHTML = `${response.elek}<span> мксм/см</span>`;
            $('div.environment div.variable h3.figure[name=density]')[0].innerHTML = `${response.density}<span> мг/л</span>`;
            $('div.control div.variable h3.figure[name=orient_z]')[0].innerHTML = `${response.orient_z}`;
            var a = $('button.menu_but')
            var index;
            if (response.valid === false) {
                for (index = 0; index < a.length; ++index) {
                    a[index].setAttribute('class', 'menu_but err')
                }
            } else {
                for (index = 0; index < a.length; ++index) {
                    a[index].setAttribute('class', 'menu_but on')
                }
            }
        },
        error: function (xhr) {
            //Do Something to handle error
        }
    });
}

$(document).ready(function () {
    gett();
    setInterval('gett()', 2500);
});
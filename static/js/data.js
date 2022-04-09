function gett(){
    $.ajax({
        url: "/data",
        type: "get",

        success: function(response) {
            $('div.environment div.variable h3.figure[name=temp]')[0].innerHTML = `${response.temp}<span> °C</span>`;
            $('div.environment div.variable h3.figure[name=elek]')[0].innerHTML = `${response.elek}<span> мксм/см</span>`;
            $('div.environment div.variable h3.figure[name=density]')[0].innerHTML = `${response.density}<span> мг/л</span>`;
            $('div.control div.variable h3.figure[name=orient_z]')[0].innerHTML = `${response.orient_z}`;
        },
        error: function(xhr) {
            //Do Something to handle error
        }
    });
}

$(document).ready(function(){
    gett();
    setInterval('gett()', 500);
});
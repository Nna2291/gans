function engine_on(pin1, pin2){
    link = "/on";
    task = "ON," + pin1 + "," + pin2;
    $.ajax({
        type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
    });
};

$(document).ready(function () {
    $("#on").click(function (e) {
        e.preventDefault();
        link = "/on";
        task = "ON,3,4";
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
        });
    });
    $("#off").click(function (e) {
        e.preventDefault();
        link = "/off";
        task = "OF,3,4";
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
        });
    });
});

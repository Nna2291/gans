$(document).ready(function () {
    $("#on").click(function (e) {
        e.preventDefault();
        link = "/on";
        task = "ON,5," + $("#mi1").val()
        $.ajax({
            type: "POST", url: link,
            contentType: "application/json",
            data: JSON.stringify({"task": task})
        });
    });
    $("#on2").click(function (e) {
        e.preventDefault();
        link = "/on";
        task = "ON,7," + $("#mi1").val()
        $.ajax({
            type: "POST", url: link,
            contentType: "application/json",
            data: JSON.stringify({"task": task})
        });
    });
    $("#off").click(function (e) {
        e.preventDefault();
        link = "/off";
        task = "OFF,5";
        $.ajax({
            type: "POST", url: link,
            contentType: "application/json",
            data: JSON.stringify({"task": task})
        });
    });
    $("#off2").click(function (e) {
        e.preventDefault();
        link = "/off";
        task = "OFF,7";
        $.ajax({
            type: "POST", url: link,
            contentType: "application/json",
            data: JSON.stringify({"task": task})
        });
    });
});

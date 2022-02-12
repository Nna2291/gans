$(document).ready(function () {
    $("#on").click(function (e) {
        e.preventDefault();
        link = "/on";
        task = "ON," + $("#mi1").val() + "," + $("#mi2").val();
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
        });
    });
    $("#off").click(function (e) {
        e.preventDefault();
        link = "/off";
        task = "OF," + $("#mi1").val() + "," + $("#mi2").val();
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
        });
    });
    $("#on_l").click(function (e) {
        e.preventDefault();
        link = "/on_l";
        task = "OL," + $("#mi3").val() + "," + $("#mi4").val();
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
        });
    });
    $("#off_l").click(function (e) {
        e.preventDefault();
        link = "/off_l";
        task = "FL," + $("#mi3").val() ;
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
        });
    });
});

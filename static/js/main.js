$(document).ready(function () {


    $("#on").click(function (e) {
        e.preventDefault();
        $.ajax({
            type: "POST", url: "/on",
        });
    });
    $("#off").click(function (e) {
        e.preventDefault();
        $.ajax({
            type: "POST", url: "/off",
        });
    });
    $("#on1").click(function (e) {
        e.preventDefault();
        $.ajax({
            type: "POST", url: "/oon",
        });
    });
    $("#off1").click(function (e) {
        e.preventDefault();
        $.ajax({
            type: "POST", url: "/ooff",
        });
    });
});

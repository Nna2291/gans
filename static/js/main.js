$(document).ready(function () {
    $("#on").click(function (e) {
        e.preventDefault();
        link = "/on/" + $("#mi1").val();
        $.ajax({
            type: "POST", url: link,
        });
    });
    $("#off").click(function (e) {
        e.preventDefault();
        link = "/off/" + $("#mi1").val();
        $.ajax({
            type: "POST", url: link,
        });
    });
});

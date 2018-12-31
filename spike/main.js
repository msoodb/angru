
$( document ).ready(function() {
    var values = {
      "email":"masoud@gmail.com",
    	"password":"1234",
    	"details":""
    }
    $('.ajax_form').on('submit', function (e) {
        e.preventDefault();
        $.ajax({
            url: "http://198.143.183.251:9080/login",
            //url: "http://127.0.0.1:9080/login",
            type: "post",
            headers: {
                'Content-Type':'application/json'
            },
            dataType: 'json',
            data:JSON.stringify({"email":"masoud@gmail.com","password":"1234","details":""}) ,
            success: function (response) {
                // you will get response from your php page (what you echo or print)
                console.log(response)
            },
            error: function(jqXHR, textStatus, errorThrown) {
                console.log(textStatus, errorThrown, jqXHR);
            }
        });
    })
});

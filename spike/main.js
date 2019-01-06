
$( document ).ready(function() {
    var values = {
      "email":"masoud@gmail.com",
    	"password":"1234",
    	"details":""
    }
    $('.ajax_form').on('submit', function (e) {
        e.preventDefault();
        $.ajax({
            //url: "http://198.143.183.251/users",
            url: "http://127.0.0.1:9080/login",
            type: "get",
            headers: {
                'Content-Type':'application/json',
                'Authorization': 'eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJleHAiOjE1NDY1Mjg4NzgsImlhdCI6MTUxMzg2MjM3MSwiaWQiOiJtYXNvdWQuYkBnbWFpbC5jb20iLCJpc3MiOiJtYXNvdWQuYkBnbWFpbC5jb20iLCJzdWIiOiJ0ZXN0IiwidXNlciI6ImFkbWluIn0.skhXJIcWsxpzStMMR_wslYZzUJGSsngHBWhoZZqwOm0'
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

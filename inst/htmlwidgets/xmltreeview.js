//function $qs(css) { return(document.querySelector(css)) }

HTMLWidgets.widget({

  name: 'xmltreeview',
  type: 'output',

  factory: function(el, width, height) {

    return {

      view: { },

      renderValue: function(param) {

        //empty el in case of dynamic/Shiny
        el.innerHTML = "";

        //add CSS overflow scroll to el
        if (param.scroll) { el.style.overflow = "scroll" }

        var docSpec = {
          unknownElement: {
            isReadOnly: true
          },
          unknownAttribute: {
            isReadOnly: true
          }
        };

        Xonomy.setMode(param.mode);
        Xonomy.render(param.xmlDoc, el, docSpec);
        Xonomy.setMode(param.mode);

      },

      resize: function(width, height) { }

    };

  }

});



function $qs(css) { return(document.querySelector(css)) }

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

        var view = new Viewer(param.xmlDoc);
        view.appendTo(el);

        this.view = view;

      },

      resize: function(width, height) { }

    };

  }

});
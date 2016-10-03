// shortcuts (kinda the only reason I use jQuery anyway)
function $id(element) { return(document.getElementById(element)); }
function $tag(tag) { return(document.getElementsByTagName(tag)); }
function $qs(css) { return(document.querySelector(css)) }

HTMLWidgets.widget({

  name: 'xmlview',
  type: 'output',

  initialize: function(el, width, height) { return {} },

  renderValue: function(el, param, instance) {

    var self = this;

    self.thel = el;
    self.glob = {} ;

    function filter_xpath() {
      self.msg.style.display = "none";
      do_filter(self.xpath.value.trim());
    }

    function do_filter(xpath) {

      self.rcode.style.display = "none";

      if (xpath === "") return(reset_form());

      var out_xml = "" ;

      try {

        var nsResolver = self.glob.parsedOrig.createNSResolver(
                                    self.glob.parsedOrig);

        var results =
          self.glob.parsedOrig.evaluate(xpath,
                           self.glob.parsedOrig,
                           nsResolver,
                           XPathResult.UNORDERED_NODE_ITERATOR_TYPE,
                           null);

        var res = results.iterateNext() ;

        while(res) {
          out_xml = out_xml + self.glob.serialize.serializeToString(res);
          res = results.iterateNext();
        }

        self.xml_div.innerText = vkbeautify.xml(out_xml);
        self.xml_div.textContent = vkbeautify.xml(out_xml);

        hljs.highlightBlock(self.xml_div);

      } catch(err) {

        self.msg.innerText = "Invalid XPath";
        self.msg.textContent = "Invalid XPath";
        self.msg.style.display = "inline-block";

      }

    }

    function reset_form(doc) {

      self.rcode.style.display = "none";
      self.msg.style.display = "none";
      self.xpath.value = "" ;

      self.xml_div.innerText = vkbeautify.xml(self.glob.xmlDoc);
      self.xml_div.textContent = vkbeautify.xml(self.glob.xmlDoc);

      hljs.highlightBlock(self.xml_div);

      return(false);

    }

    function generate_rcode() {

      self.rcode.innerText = "xml2::xml_find_all(" +
                              self.glob.xmlDocName + ", '" +
                              self.xpath.value + "', ns=xml2::xml_ns(" +
                              self.glob.xmlDocName + "))";
      self.rcode.textContent = "xml2::xml_find_all(" +
                               self.glob.xmlDocName + ", '" +
                               self.xpath.value + "', ns=xml2::xml_ns(" +
                               self.glob.xmlDocName + "))";
      self.rcode.style.display = "inline-block";

      return(false);

    }

    var serializer = new XMLSerializer();
    var domparser =  new DOMParser();

    self.glob.xmlDocName = param.xmlDocName;
    self.glob.xmlDoc     = param.xmlDoc;
    self.glob.applyXPath = param.applyXPath;
    self.glob.orig       = param.xmlDoc;
    self.glob.serialize  = serializer;
    self.glob.parser     = domparser;
    self.glob.parsedOrig = domparser.parseFromString(param.xmlDoc,
                           "text/xml");

    var link = document.createElement("link");
    link.href  = "lib/highlightjs-9.0.0/styles/" +
                 param.styleSheet + ".css";
    link.type  = "text/css";
    link.rel   = "stylesheet";
    link.media = "screen,print";

    $tag("head")[0].appendChild(link);

    if (param.scroll) { el.style.overflow = "scroll" }

    var msg = '<div class="msgdiv"></div>';
    var rcode = '<div class="rcodediv"></div>';

    var filter = "";

    if (param.addFilter) {
      filter = '<div class="filterdiv">' +
               '<span class="xpathspan">XPath:</span> ' +
               '<input title="Enter XPath to test and hit ENTER/RETURN. Errors will indicate a bad XPath, otherwise the document contents will reflect the outcome of the XPath selection." class="filterinput" type="text" size=69 id="xpath"/> ' +
               '<button title="Reset XPath & restore original document" class="resetclass"></button> ' +
               '<button alt="Generate R xml2 code" title="Generate R xml2 code" class="rcodeclass"></button>' +
               '</div>';
    }

    el.innerHTML = filter + msg + rcode +
      '<pre><code class="html xmldiv"></code></pre>';

    if (param.addFilter) {
      $qs("div#" + el.id + " > div.filterdiv > input.filterinput").onchange = filter_xpath;
      $qs("div#" + el.id + " > div.filterdiv > button.resetclass").onclick = reset_form;
      $qs("div#" + el.id + " > div.filterdiv > button.rcodeclass").onclick = generate_rcode;
    }

    self.xml_div = $qs("div#" + el.id + " > pre > code.xmldiv");
    self.msg = $qs("div#" +  el.id + " > div.msgdiv");
    self.xpath = $qs("div#" + el.id + " > div.filterdiv > input.filterinput");
    self.rcode = $qs("div#" + el.id + " > div.rcodediv");

    if (self.glob.applyXPath === null) {

      self.xml_div.innerText = vkbeautify.xml(param.xmlDoc);
      self.xml_div.textContent = vkbeautify.xml(param.xmlDoc);

      hljs.initHighlighting() ;
      hljs.highlightBlock(self.xml_div);

    } else {
      if (param.addFilter) { $qs("div#" + el.id + " > div.filterdiv > input.filterinput").value = param.applyXPath }
      do_filter(param.applyXPath);
    }

  },

  resize: function(el, width, height, instance) {},

});

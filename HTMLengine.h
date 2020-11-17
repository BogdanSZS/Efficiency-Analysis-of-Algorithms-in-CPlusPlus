#ifndef _HTML_ENGINE_H
#define _HTML_ENGINE_H
#ifdef _MSC_VER
#   include <Windows.h>
#   include <Shellapi.h>
#endif
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;


class HTMLengine 
{
private:
	string nodes;
	string edges;

public:
	void GorgeousGenerate()
	{
		char reportName[200];
		time_t crtTime = time(0);
		struct tm now;
		#ifdef _MSC_VER
				localtime_s(&now, &crtTime);
		#else
				now = *localtime(&crtTime);
		#endif

		#ifdef _MSC_VER
				_snprintf_s(
		#else
				snprintf(
		#endif
			reportName, sizeof(reportName), "gorgeous-generate-%04d%02d%02d-%02d%02d%02d.html",  now.tm_year + 1900, now.tm_mon + 1, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);

		std::ofstream report;
		report.open(reportName, std::ios::trunc);
		report << "<html> <head> <title>cytoscape-dagre.js demo</title> <meta name=\"viewport\" content=\"width=device-width, user-scalable=no, initial-scale=1, maximum-scale=1\"> <script src=\"https://unpkg.com/cytoscape/dist/cytoscape.min.js\"></script> <script src=\"https://unpkg.com/dagre@0.7.4/dist/dagre.js\"></script> <script>!function(e,n){\"object\"==typeof exports&&\"object\"==typeof module?module.exports=n(require(\"dagre\")):\"function\"==typeof define&&define.amd?define([\"dagre\"],n):\"object\"==typeof exports?exports.cytoscapeDagre=n(require(\"dagre\")):e.cytoscapeDagre=n(e.dagre)}(window,function(t){return i={},o.m=r=[function(e,n,t){function r(e){e&&e(\"layout\",\"dagre\",o)}var o=t(1);\"undefined\"!=typeof cytoscape&&r(cytoscape),e.exports=r},function(e,n,t){function S(e){return(S=\"function\"==typeof Symbol&&\"symbol\"==typeof Symbol.iterator?function(e){return typeof e}:function(e){return e&&\"function\"==typeof Symbol&&e.constructor===Symbol&&e!==Symbol.prototype?\"symbol\":typeof e})(e)}var r=t(2),o=t(3),j=t(4);function i(e){this.options=o({},r,e)}i.prototype.run=function(){function e(e,n){return\"function\"==typeof n?n.apply(e,[e]):n}var r=this.options,n=r.cy,t=r.eles,o=r.boundingBox||{x1:0,y1:0,w:n.width(),h:n.height()};void 0===o.x2&&(o.x2=o.x1+o.w),void 0===o.w&&(o.w=o.x2-o.x1),void 0===o.y2&&(o.y2=o.y1+o.h),void 0===o.h&&(o.h=o.y2-o.y1);function i(e,n){null!=n&&(u[e]=n)}var a=new j.graphlib.Graph({multigraph:!0,compound:!0}),u={};i(\"nodesep\",r.nodeSep),i(\"edgesep\",r.edgeSep),i(\"ranksep\",r.rankSep),i(\"rankdir\",r.rankDir),i(\"ranker\",r.ranker),a.setGraph(u),a.setDefaultEdgeLabel(function(){return{}}),a.setDefaultNodeLabel(function(){return{}});for(var c=t.nodes(),d=0;d<c.length;d++){var f=c[d],s=f.layoutDimensions(r);a.setNode(f.id(),{width:s.w,height:s.h,name:f.id()})}for(var y=0;y<c.length;y++){var p=c[y];p.isChild()&&a.setParent(p.id(),p.parent().id())}for(var l=t.edges().stdFilter(function(e){return!e.source().isParent()&&!e.target().isParent()}),g=0;g<l.length;g++){var h=l[g];a.setEdge(h.source().id(),h.target().id(),{minlen:e(h,r.minLen),weight:e(h,r.edgeWeight),name:h.id()},h.id())}j.layout(a);for(var x,b=a.nodes(),v=0;v<b.length;v++){var m=b[v],w=a.node(m);n.getElementById(m).scratch().dagre=w}r.boundingBox?(x={x1:1/0,x2:-1/0,y1:1/0,y2:-1/0},c.forEach(function(e){var n=e.scratch().dagre;x.x1=Math.min(x.x1,n.x),x.x2=Math.max(x.x2,n.x),x.y1=Math.min(x.y1,n.y),x.y2=Math.max(x.y2,n.y)}),x.w=x.x2-x.x1,x.h=x.y2-x.y1):x=o;return c.layoutPositions(this,r,function(e){var n=(e=\"object\"===S(e)?e:this).scratch().dagre;return function(e){if(r.boundingBox){var n=0===x.w?0:(e.x-x.x1)/x.w,t=0===x.h?0:(e.y-x.y1)/x.h;return{x:o.x1+n*o.w,y:o.y1+t*o.h}}return e}({x:n.x,y:n.y})}),this},e.exports=i},function(e,n){var t={nodeSep:void 0,edgeSep:void 0,rankSep:void 0,rankDir:void 0,ranker:void 0,minLen:function(){return 1},edgeWeight:function(){return 1},fit:!0,padding:30,spacingFactor:void 0,nodeDimensionsIncludeLabels:!1,animate:!1,animateFilter:function(){return!0},animationDuration:500,animationEasing:void 0,boundingBox:void 0,transform:function(e,n){return n},ready:function(){},stop:function(){}};e.exports=t},function(e,n){e.exports=null!=Object.assign?Object.assign.bind(Object):function(t){for(var e=arguments.length,n=new Array(1<e?e-1:0),r=1;r<e;r++)n[r-1]=arguments[r];return n.forEach(function(n){Object.keys(n).forEach(function(e){return t[e]=n[e]})}),t}},function(e,n){e.exports=t}],o.c=i,o.d=function(e,n,t){o.o(e,n)||Object.defineProperty(e,n,{enumerable:!0,get:t})},o.r=function(e){\"undefined\"!=typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(e,Symbol.toStringTag,{value:\"Module\"}),Object.defineProperty(e,\"__esModule\",{value:!0})},o.t=function(n,e){if(1&e&&(n=o(n)),8&e)return n;if(4&e&&\"object\"==typeof n&&n&&n.__esModule)return n;var t=Object.create(null);if(o.r(t),Object.defineProperty(t,\"default\",{enumerable:!0,value:n}),2&e&&\"string\"!=typeof n)for(var r in n)o.d(t,r,function(e){return n[e]}.bind(null,r));return t},o.n=function(e){var n=e&&e.__esModule?function(){return e.default}:function(){return e};return o.d(n,\"a\",n),n},o.o=function(e,n){return Object.prototype.hasOwnProperty.call(e,n)},o.p=\"\",o(o.s=0);function o(e){if(i[e])return i[e].exports;var n=i[e]={i:e,l:!1,exports:{}};return r[e].call(n.exports,n,n.exports,o),n.l=!0,n.exports}var r,i});</script> <style>body{font-family: helvetica; font-size: 14px;}#cy{width: 100%; height: 100%; position: absolute; left: 0; top: 0; z-index: 999;}h1{opacity: 0.5; font-size: 1em;}</style> <script>window.addEventListener('DOMContentLoaded', function(){var cy=window.cy=cytoscape({container: document.getElementById('cy'),boxSelectionEnabled: false,autounselectify: true,layout:{name: 'dagre'}, style: [{selector: 'node',style:{'background-color': 'data(color)','content': 'data(title)'}},{selector: 'edge', style:{'width': 4,'target-arrow-shape': 'triangle','line-color': '#9dbaea','target-arrow-color': '#9dbaea','curve-style': 'bezier'}}], elements:{nodes: [";
		report << nodes;
		report << "],edges: [";
		report << edges;
		report << "]}});}); </script> </head> <body> <h1>powered by cytoscape</h1> <div id=\"cy\"></div></body></html>";
		report.close();
		#ifdef _MSC_VER
				ShellExecuteA(NULL, "open", reportName, NULL, NULL, 5);
		#endif
	}

	void addNode(string op, int val, string color)
	{
		this->nodes = this->nodes + "{ data: {id:'" + op + to_string(val) + "', title:'" + to_string(val) + "',color:'" + color + "'}},";
	}

	void addEdge(string op, int val1, int val2)
	{
		this->edges = this->edges + "{ data: { source: '" + op + to_string(val1) + "', target: '" + op + to_string(val2) + "' } },";
	}
};

#endif
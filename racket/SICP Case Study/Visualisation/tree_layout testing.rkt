#lang racket
(require pict/tree-layout)
(tree-layout [#:pict node-pict] child ...) → tree-layout?

  node-pict : (or/c #f pict?) = #f
  child : (or/c tree-layout? tree-edge? #f)

(tree-edge	 	node	 	 	 	 
 	 [	#:edge-color edge-color	 	 	 	 
 	 	#:edge-width edge-width	 	 	 	 
 	 	#:edge-style edge-style])	 	→	 	tree-edge?
  node : (and/c tree-layout? (not/c #f))
  	edge-color	 	:	 	
(or/c string?
      (is-a?/c color%)
      (list/c byte? byte? byte?))
 	=	 	"gray"
  edge-width : (or/c 'unspecified real? #f) = 'unspecified
  	edge-style	 	:	 	
(or/c 'unspecified 'transparent 'solid 'xor 'hilite
      'dot 'long-dash 'short-dash 'dot-dash
      'xor-dot 'xor-long-dash 'xor-short-dash
      'xor-dot-dash)
 	 	 	=	 	'unspecified
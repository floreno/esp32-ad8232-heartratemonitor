# Human body illustration

Source: [Human body with blank labels.svg](https://commons.wikimedia.org/wiki/File:Human_body_with_blank_labels.svg), Wikimedia Commons.

Author: Šlomo. Published 18 November 2015. Source file retrieved 17 October 2026 from:
https://upload.wikimedia.org/wikipedia/commons/3/33/Human_body_with_blank_labels.svg

License: [CC0 1.0 Universal Public Domain Dedication](https://creativecommons.org/publicdomain/zero/1.0/).
The file page states the author dedicated this work to the public domain.

The original file is preserved as `vendor/human-body-with-blank-labels.svg`.
`human-body-front.svg` extracts the original front-view group `g5692`, preserving its path geometry and transformations. Annotation leaders, the back view and editor metadata were omitted. Only the line color/width, scale and framing were adjusted.

`electrode-limbs.svg` and `electrode-torso.svg` add RA (red), LA (yellow) and RL (green) markers. These marker colors follow the user's reference and are not a universal cable-color specification. Electrode placement follows the SparkFun AD8232 guide. The figure is a reusable anatomical illustration, not an ISO-certified or medically standardized electrode-placement diagram.

The firmware embeds the body paths once in a local SVG definition and reuses them for both diagrams. No internet connection is required on the ESP32.

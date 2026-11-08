// https://vitepress.dev/guide/custom-theme
import { h } from 'vue'
import type { Theme } from 'vitepress'
import DefaultTheme from 'vitepress/theme'
import './custom.css'

import RegisterSW from './components/RegisterSW.vue'
import JumpToProcedure from './components/JumpToProcedure.vue'
import ContinueReading from './components/ContinueReading.vue'

import Screenshot from './components/Screenshot.vue'

export default {
  extends: DefaultTheme,
  Layout() {
    return h(DefaultTheme.Layout, null, {
      'home-hero-actions-after': () => h(ContinueReading, { lab: 'encs5101', mode: 'card' }),
      'doc-before': () => h(JumpToProcedure),
      'layout-bottom': () => [h(RegisterSW), h(ContinueReading, { lab: 'encs5101', mode: 'track' })],
    })
  },
  enhanceApp({ app }) {
    app.component('Screenshot', Screenshot)
  },
} satisfies Theme

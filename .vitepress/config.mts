import { defineConfig } from 'vitepress'
import { withPwa } from '@vite-pwa/vitepress'

// BASE_PATH is set by the GitHub Pages workflow ("/repo-name/" or "/" with a custom domain).
const base = process.env.BASE_PATH || '/'

export default withPwa(defineConfig({
  base,
  lang: 'en-US',
  title: 'ENCS5101 Microprocessor and Embedded Systems Lab',
  description:
    'Step-by-step guides for the ENCS5101 Microprocessor and Embedded Systems Laboratory at Birzeit University.',
  srcExclude: ['README.md'],
  cleanUrls: true,
  lastUpdated: true,

  head: [
    // .ico first for browsers and tools without SVG favicon support; the SVG wins where it is supported.
    ['link', { rel: 'icon', href: `${base}favicon.ico`, sizes: 'any' }],
    ['link', { rel: 'icon', type: 'image/svg+xml', href: `${base}favicon.svg` }],
    ['link', { rel: 'apple-touch-icon', href: `${base}apple-touch-icon.png` }],
    ['meta', { name: 'theme-color', content: '#00878f' }],
    ['meta', { property: 'og:type', content: 'website' }],
    ['meta', { property: 'og:site_name', content: 'ECE Labs · Birzeit University' }],
    ['meta', { property: 'og:image', content: 'https://encs5101.birzeit.me/og.png' }],
    ['meta', { property: 'og:image:width', content: '1200' }],
    ['meta', { property: 'og:image:height', content: '630' }],
    ['meta', { name: 'twitter:card', content: 'summary_large_image' }],
    ['script', { async: '', src: 'https://www.googletagmanager.com/gtag/js?id=G-K834Q72PP9' }],
    [
      'script',
      {},
      `window.dataLayer = window.dataLayer || [];
      function gtag(){dataLayer.push(arguments);}
      gtag('js', new Date());
      gtag('config', 'G-K834Q72PP9');`,
    ],
  ],

  sitemap: { hostname: 'https://encs5101.birzeit.me/' },

  // Link previews: per-page title, the page's (or site's) description, and canonical URL.
  transformHead({ pageData, siteData }) {
    const page = pageData.frontmatter.layout === 'home' ? '' : pageData.title
    const path = pageData.relativePath.replace(/(^|\/)index\.md$/, '$1').replace(/\.md$/, '')
    return [
      ['meta', { property: 'og:title', content: page ? `${page} · ENCS5101` : 'ENCS5101 Microprocessor and Embedded Systems Laboratory' }],
      ['meta', { property: 'og:description', content: pageData.frontmatter.description || pageData.description || siteData.description }],
      ['meta', { property: 'og:url', content: `https://encs5101.birzeit.me/${path}` }],
    ]
  },

  themeConfig: {
    logo: '/favicon.svg',
    siteTitle: 'ENCS5101-BZU',

    nav: [
      { text: 'Home', link: '/' },
      { text: 'Experiments', link: '/experiments/', activeMatch: '/experiments/' },
      { text: 'All labs', link: 'https://birzeit.me/' },
    ],

    sidebar: {
      '/': [
        { text: 'Experiment Navigator', link: '/experiments/' },
        {
          text: 'Getting Started',
          link: '/setup/',
          collapsed: true,
          items: [
            { text: 'Keil uVision5', link: '/setup/keil' },
            { text: 'Arduino IDE', link: '/setup/arduino' },
          ],
        },
        {
          text: 'Experiments',
          collapsed: false,
          items: [
            { text: '1. ARM Assembly and Keil', link: '/experiments/exp1-arm-basics' },
            { text: '2. Flow Control', link: '/experiments/exp2-flow-control' },
            { text: '3. Arduino Basics', link: '/experiments/exp3-arduino-intro' },
          ],
        },
        {
          // Downloads + Documentation are pushed to the sidebar bottom in custom.css.
          text: 'Downloads',
          collapsed: true,
          items: [
            { text: 'Keil MDK', link: 'https://www.keil.arm.com/mdk-community/' },
            { text: 'Arduino IDE', link: 'https://www.arduino.cc/en/software' },
            // `base` by hand: a sidebar item with target '_blank' counts as external,
            // so VitePress does not prefix it for us.
            { text: 'Full Lab Manual (PDF)', link: `${base}ENCS5101-Manual.pdf`, target: '_blank' },
          ],
        },
        {
          text: 'Documentation',
          collapsed: true,
          items: [
            { text: 'Cortex-M4 Generic User Guide', link: 'https://developer.arm.com/documentation/dui0553/latest/' },
            { text: 'armasm User Guide (directives)', link: 'https://developer.arm.com/documentation/dui0473/latest/' },
            { text: 'Arduino Mega 2560 Docs', link: 'https://docs.arduino.cc/hardware/mega-2560/' },
            { text: 'Arduino Mega Full Pinout (PDF)', link: 'https://docs.arduino.cc/resources/pinouts/A000067-full-pinout.pdf' },
            { text: 'Arduino Language Reference', link: 'https://docs.arduino.cc/language-reference/' },
            { text: 'ATmega2560 Datasheet', link: 'https://ww1.microchip.com/downloads/en/devicedoc/atmel-2549-8-bit-avr-microcontroller-atmega640-1280-1281-2560-2561_datasheet.pdf' },
          ],
        },
      ],
    },

    outline: { level: [2, 3] },

    search: { provider: 'local' },

    editLink: {
      pattern: 'https://github.com/ECE-Birzeit/encs5101/edit/main/:path',
      text: 'Edit this page on GitHub',
    },

    socialLinks: [
      { icon: 'github', link: 'https://github.com/ECE-Birzeit/encs5101' },
    ],

    footer: {
      message: 'ENCS5101 · Microprocessor and Embedded Systems Laboratory',
      copyright: 'Developed by <a href="https://mabushelbaia.com" target="_blank">Mohammad Abu-Shelbaia</a>',
    },
  },

  // Installable, offline-capable app. Icons are rendered from favicon.svg (the sidebar logo).
  pwa: {
    registerType: 'autoUpdate',
    manifest: {
      name: 'ENCS5101 Microprocessor and Embedded Systems Laboratory',
      short_name: 'ENCS5101',
      description:
        'Step-by-step guides for the ENCS5101 Microprocessor and Embedded Systems Laboratory at Birzeit University.',
      theme_color: '#00878f',
      background_color: '#ffffff',
      display: 'standalone',
      scope: base,
      start_url: base,
      icons: [
        { src: `${base}icons/pwa-192x192.png`, sizes: '192x192', type: 'image/png' },
        { src: `${base}icons/pwa-512x512.png`, sizes: '512x512', type: 'image/png' },
        { src: `${base}icons/maskable-512x512.png`, sizes: '512x512', type: 'image/png', purpose: 'maskable' },
        { src: `${base}favicon.svg`, sizes: 'any', type: 'image/svg+xml' },
      ],
    },
    workbox: {
      // The manual PDF is left out: it is too large to precache, and the guides do not need it offline.
      globPatterns: ['**/*.{css,js,html,svg,png,jpg,jpeg,webp,ico,txt,woff2}'],
      maximumFileSizeToCacheInBytes: 5000000,
    },
    experimental: {
      includeAllowlist: true,
    },
  },
}))

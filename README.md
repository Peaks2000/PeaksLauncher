<p align="center">
  <img alt="PeaksLauncher barrier block logo" src="/program_info/io.github.Peaks2000.PeaksLauncher.svg" width="20%">
</p>

# PeaksLauncher

PeaksLauncher is a fork of [Prism Launcher](https://github.com/PrismLauncher/PrismLauncher) for managing Minecraft instances. It adds a **Syncing** settings page: enable sharing of `options.txt` between instances, or choose an instance whose options the others inherit when launched. The barrier block over the Prism logo is a joke about keeping instance settings under control.

This project is not endorsed by or affiliated with the Prism Launcher project or MultiMC.

## Installation

Download the RPM or DEB from [PeaksLauncher releases](https://github.com/Peaks2000/PeaksLauncher/releases). The package installs as `peakslauncher` with its own configuration and data directory, so it can coexist with Prism Launcher.

This fork does not have its own Microsoft or CurseForge API credentials. Those services are unavailable in the published packages until fork-specific credentials are configured. See `CMakeLists.txt` if building your own copy.

## Building

Follow the [upstream build instructions](https://prismlauncher.org/wiki/development/build-instructions) with this repository as the source. Linux builds use CMake and Qt 6. The Debian build dependency list is in [`packaging/Dockerfile.deb`](packaging/Dockerfile.deb).

For project issues, use the [PeaksLauncher issue tracker](https://github.com/Peaks2000/PeaksLauncher/issues).

## Translations

The translation effort for Prism Launcher is hosted on [Weblate](https://hosted.weblate.org/projects/prismlauncher/launcher/) and information about translating Prism Launcher is available at <https://github.com/PrismLauncher/Translations>.

## Building

If you want to build Prism Launcher yourself, check the [build instructions](https://prismlauncher.org/wiki/development/build-instructions).

## Upstream sponsors and partners

Prism Launcher thanks its backers at Open Collective. Support the upstream project by [becoming a backer](https://opencollective.com/prismlauncher).

[![OpenCollective Backers](https://opencollective.com/prismlauncher/backers.svg?width=890&limit=1000)](https://opencollective.com/prismlauncher#backers)

The upstream project acknowledges JetBrains for support through its [Open Source program](https://www.jetbrains.com/opensource/).

<a href="https://jb.gg/OpenSource">
<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://www.jetbrains.com/company/brand/img/logo_jb_dos_4.svg">
  <source media="(prefers-color-scheme: light)" srcset="https://resources.jetbrains.com/storage/products/company/brand/logos/jetbrains.svg">
  <img alt="JetBrains logo" src="https://resources.jetbrains.com/storage/products/company/brand/logos/jetbrains.svg" width="40%">
</picture>
</a>

The upstream project uses Weblate for translations.

<a href="https://hosted.weblate.org/engage/prismlauncher/">
<img src="https://hosted.weblate.org/widgets/prismlauncher/-/open-graph.png" alt="Translation status" width="300" />
</a>

The upstream project acknowledges Netlify for web hosting through its [Open Source program](https://www.netlify.com/open-source/).

<a href="https://www.netlify.com"> <img src="https://www.netlify.com/v3/img/components/netlify-color-accent.svg" alt="Deploys by Netlify" /> </a>

The upstream project acknowledges [MacStadium](https://www.macstadium.com/) for providing Macs for development.

<a href="https://www.macstadium.com"><img src="https://uploads-ssl.webflow.com/5ac3c046c82724970fc60918/5c019d917bba312af7553b49_MacStadium-developerlogo.png" alt="Powered by MacStadium" width="300"></a>

## Forking/Redistributing/Custom builds policy

You are free to fork, redistribute and provide custom builds as long as you follow the terms of the [license](LICENSE) (this is a legal responsibility), and if you made code changes rather than just packaging a custom build, please do the following as a basic courtesy:

- Make it clear that your fork is not Prism Launcher and is not endorsed by or affiliated with the Prism Launcher project (<https://prismlauncher.org>).
- Go through [CMakeLists.txt](CMakeLists.txt) and change Prism Launcher's API keys to your own or set them to empty strings (`""`) to disable them (this way the program will still compile but the functionality requiring those keys will be disabled).

If you have any questions or want any clarification on the above conditions please make an issue and ask us.

If you are just building Prism Launcher for your distribution, please make sure to set the `Launcher_BUILD_PLATFORM` to a slug representing your distribution. Examples are `archlinux`, `fedora` and `nixpkgs`.

Note that if you build this software without removing the provided API keys in [CMakeLists.txt](CMakeLists.txt) you are accepting the following terms and conditions:

- [Microsoft Identity Platform Terms of Use](https://docs.microsoft.com/en-us/legal/microsoft-identity-platform/terms-of-use)
- [CurseForge 3rd Party API Terms and Conditions](https://support.curseforge.com/en/support/solutions/articles/9000207405-curse-forge-3rd-party-api-terms-and-conditions)

If you do not agree with these terms and conditions, then remove the associated API keys from the [CMakeLists.txt](CMakeLists.txt) file by setting them to an empty string (`""`).

## License [![https://github.com/PrismLauncher/PrismLauncher/blob/develop/LICENSE](https://img.shields.io/github/license/PrismLauncher/PrismLauncher?label=License&logo=gnu&color=C4282D)](LICENSE)

All launcher code is available under the GPL-3.0-only license.

The logo and related assets are under the CC BY-SA 4.0 license.

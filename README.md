# Comment Sort Weight

This module displays comments newest first or oldest first by date on a per
content type basis. It is a port of the Drupal 7 Comment Sort Weight module,
with a fix for a permalink/pagination issue the original module did not address.

## Instructions

- Install this module using the official Backdrop CMS instructions at
  https://docs.backdropcms.org/documentation/extend-with-modules.

- Configure content types (`admin/structure/types/manage/[content_type]`), go to
  **Comment settings** and check the box **Sort comments by weight** for options.

## What the module does

Per content type, the module lets you configure:

- Whether comments use a custom display order at all.
- Newest-first or oldest-first for root-level comments.
- Whether replies under each comment should also reverse, or keep their
  default oldest-first order regardless of the root setting.

## How it works

A `comment_sort_weight` table stores one precomputed `weight` value per
comment, built by flattening the comment tree in the configured order.
`hook_query_TAG_alter()` targets Backdrop's `comment_filter` query tag in
`comment_get_thread()` and swaps in an ORDER BY on that weight column for
threaded listings, or a direct ASC/DESC swap on `c.created` for flat listings.

The table is resynced on comment insert/update/delete, and in bulk via a
batch operation when a content type's settings are saved.

To correct comment permalinks or pager-page calculation when the sort order is
reversed this module computes the comment's correct page via
`comment_sort_weight_get_display_ordinal()`, querying the weight table
directly with no need for branching on sort direction since it's baked into the
weight at write time, and uses a `backdrop_goto()` redirect to
`node/[nid]?page=[n]#comment-[cid]` to avoid bypassing Backdrop's layout system;
matching the fix that was merged for the Backdrop forum [Permalinks issue](https://github.com/backdrop-ops/forum.backdropcms.org/issues/44).

## Views integration

- **Views integration.** This was ported from the Drupal 7 module as
  `comment_sort_weight.views.inc`, exposing the `weight` column as a
  sortable/filterable/field-able Views column via `hook_views_data()`.
  **Note:** this only helps *custom* Views-based comment listings
  (e.g. a "recent comments" block) - it is a separate mechanism from the
  `hook_query_TAG_alter()` in this module that applies to the *default* comment
  display for a content type node, which doesn't go through Views at all.

## Documentation <!-- Do not include if you have not created a wiki page. -->

Additional documentation is located in [the Wiki](https://github.com/backdrop-contrib/comment_sort_weight/wiki/Documentation).

## Current Maintainers

- [izmeez](https://github.com/izmeez).
<!-- You may also wish to add: -->
- Seeking additional maintainers.

## Credits

- Ported to Backdrop CMS by [izmeez](https://github.com/izmeez). Assisted-by: LLM agent.
- Originally written for Drupal by [pol](https://github.com/drupol).

## License

This project is GPL v2 software.
See the LICENSE.txt file in this directory for complete text.

<!-- If your project includes other libraries that are licensed in a way that is
compatible with GPL v2, you can list that here too, for example: `Foo library is
licensed under the MIT license.` -->

<?php
/**
 * @file
 * Provide Views data and handlers for comment_sort_weight.module.
 *
 * @ingroup views_module_handlers
 */

/**
 * Implements hook_views_data().
 *
 * Exposes the precomputed weight column so custom Views-based comment
 * listings can sort by it, separate from the default node comment
 * display handled by comment_sort_weight_query_comment_filter_alter().
 */
function comment_sort_weight_views_data() {
  $data['comment_sort_weight']['table']['group'] = t('Comment');

  $data['comment_sort_weight']['table']['join'] = array(
    'comment' => array(
      'left_field' => 'cid',
      'field' => 'cid',
    ),
  );

  $data['comment_sort_weight']['weight'] = array(
    'title' => t('Sort weight'),
    'help' => t('The precomputed display order for this comment, as configured by the Comment Sort Weight module.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  return $data;
}
